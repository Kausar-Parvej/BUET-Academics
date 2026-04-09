// =============================================================================
// mtbank.cpp  —  Multi-teller bank simulation using Process Interaction
//
// Models a bank with separate queues per teller and jockeying.
// Runs for each teller count in [min_tellers, max_tellers] and reports:
//   • Time-average total number of customers in queue
//   • Average and maximum delay in queue
// =============================================================================

#include "simlib.hpp"
#include <iostream>
#include <iomanip>
#include <cstring>

// ── Event / process tags ──────────────────────────────────────────────────────
static const int EVENT_ARRIVAL      = 1;  // Next customer arrives
static const int EVENT_CLOSE_DOORS  = 3;  // Bank closes at end of day
static const int EVENT_SERVICE_DONE = 4;  // A teller finishes serving

// ── Statistical variable tags ─────────────────────────────────────────────────
static const int SAMPST_DELAYS = 1;       // sampst variable for queue delays

// ── Random-stream assignments ─────────────────────────────────────────────────
static const int STREAM_INTERARRIVAL = 1;
static const int STREAM_SERVICE      = 2;

// ── Simulation parameters (read from input file) ─────────────────────────────
static int   min_tellers;
static int   max_tellers;
static int   num_tellers;
static float mean_interarrival;
static float mean_service;
static float length_doors_open;   // Bank open for this many hours

// ── Run-time state ────────────────────────────────────────────────────────────
static int   doors_open = 1;      // 1 while bank accepts new arrivals

// ── File handles ──────────────────────────────────────────────────────────────
static FILE *infile  = nullptr;
static FILE *outfile = nullptr;

// ── Per-teller process handles ────────────────────────────────────────────────
static ProcessControlBlock *teller_processes[MAX_TELLERS + 1];

// ── Forward declarations ──────────────────────────────────────────────────────
void arrival_process();
void customer_process();
void teller_process(int teller_num);
void jockey(int teller);
int  find_shortest_queue();
void report();

// =============================================================================
//  MAIN — User's Program Routine
// =============================================================================
int main()
{
    // Open I/O files
    infile  = fopen("mtbank.in",  "r");
    outfile = fopen("mtbank.out", "w");

    if (infile == nullptr || outfile == nullptr) {
        std::cerr << "Error: could not open mtbank.in or mtbank.out\n";
        return 1;
    }

    // Read simulation parameters
    fscanf(infile, "%d %d %f %f %f",
           &min_tellers, &max_tellers,
           &mean_interarrival, &mean_service, &length_doors_open);

    // ── Header block ────────────────────────────────────────────────────────

    std::cout << "\n============================================================\n";
    std::cout << "  Multi-Teller Bank Simulation  --  Process Interaction\n";
    std::cout << "  Separate queues with jockeying\n";
    std::cout << "============================================================\n";
    std::cout << "  Teller range      : " << min_tellers << " to " << max_tellers << "\n";
    std::cout << "  Mean interarrival : " << std::fixed << std::setprecision(3)
              << mean_interarrival << " min\n";
    std::cout << "  Mean service time : " << mean_service << " min\n";
    std::cout << "  Bank hours        : " << length_doors_open << " hr\n";
    std::cout << "============================================================\n\n";

    fprintf(outfile, "Multiteller bank simulation — Process Interaction\n");
    fprintf(outfile, "Separate queues with jockeying\n\n");
    fprintf(outfile, "Teller range       : %d to %d\n\n", min_tellers, max_tellers);
    fprintf(outfile, "Mean interarrival  : %.3f minutes\n\n", mean_interarrival);
    fprintf(outfile, "Mean service time  : %.3f minutes\n\n", mean_service);
    fprintf(outfile, "Bank open for      : %.3f hours\n\n\n", length_doors_open);

    // ── Outer loop — one full simulation day per teller count ──────────────

    for (num_tellers = min_tellers; num_tellers <= max_tellers; ++num_tellers) {

        // Reinitialise simlib and process layer for a fresh day
        init_simlib();
        maxatr = 4;                // We use attributes 1..3 beyond [0]

        init_process_system();
        doors_open = 1;

        // Create one teller process per teller, each starting in CES
        // (they wait there until a customer activates them)
        for (int t = 1; t <= num_tellers; ++t) {
            teller_processes[t] = create_process(PROCESS_TYPE_TELLER, t);
            put_in_ces(teller_processes[t]);
        }

        // Schedule the first customer arrival and the end-of-day event
        event_schedule(expon(mean_interarrival, STREAM_INTERARRIVAL),
                       EVENT_ARRIVAL);
        event_schedule(60.0f * length_doors_open, EVENT_CLOSE_DOORS);

        // ── Main event loop: TIMING ROUTINE ─────────────────────────────────
        while (list_size[LIST_EVENT] != 0) {

            timing();   // Advance clock to next event, set next_event_type

            switch (next_event_type) {

                case EVENT_ARRIVAL:
                    arrival_process();
                    break;

                case EVENT_CLOSE_DOORS:
                    doors_open = 0;
                    event_cancel(EVENT_ARRIVAL);   // No more new arrivals
                    break;

                case EVENT_SERVICE_DONE: {
                    int teller_num = static_cast<int>(transfer[3]);
                    teller_process(teller_num);
                    break;
                }
            }
        }

        // Print and record results for this teller count
        report();

        // Release teller PCBs
        for (int t = 1; t <= num_tellers; ++t) {
            if (teller_processes[t] != nullptr) {
                destroy_process(teller_processes[t]);
                teller_processes[t] = nullptr;
            }
        }
    }

    fclose(infile);
    fclose(outfile);

    std::cout << "\nSimulation complete.  Results written to mtbank.out\n\n";
    return 0;
}

// =============================================================================
//  ARRIVAL PROCESS — schedules the next arrival, then spawns a customer
// =============================================================================
void arrival_process()
{
    // While the bank is still open, schedule the next customer
    if (doors_open) {
        event_schedule(sim_time + expon(mean_interarrival, STREAM_INTERARRIVAL),
                       EVENT_ARRIVAL);
    }

    // Spawn and execute the customer process for this arrival
    customer_process();
}

// =============================================================================
//  CUSTOMER PROCESS — each arriving customer's lifecycle
// =============================================================================
void customer_process()
{
    ProcessControlBlock *customer_pcb;
    ProcessControlBlock *idle_teller_pcb;
    int   selected_queue;
    float arrival_time;

    // Create a PCB to represent this customer
    customer_pcb  = create_process(PROCESS_TYPE_CUSTOMER, 0);
    arrival_time  = sim_time;

    // ── Is any teller idle? ──────────────────────────────────────────────────
    idle_teller_pcb = find_idle_teller(num_tellers);

    if (idle_teller_pcb != nullptr) {

        // A teller is free — no queueing delay
        int idle_t = idle_teller_pcb->teller_number;

        sampst(0.0f, SAMPST_DELAYS);    // Record zero delay for this customer

        // Deposit customer info in transfer[] before activating the teller
        transfer[1] = arrival_time;
        transfer[3] = static_cast<float>(idle_t);

        // Mark teller as busy (file a token in the teller's "busy" list)
        list_file(FIRST, num_tellers + idle_t);

        // Wake the teller from CES
        remove_from_ces(idle_teller_pcb);

        // Schedule service completion for this customer
        event_schedule(sim_time + expon(mean_service, STREAM_SERVICE),
                       EVENT_SERVICE_DONE);

    } else {

        // All tellers busy — join the shortest (leftmost on tie) queue
        selected_queue = find_shortest_queue();

        transfer[1] = arrival_time;
        list_file(LAST, selected_queue);   // Customer queues here

        // The teller process will dequeue and serve this customer later
    }

    // Customer's "arrival" phase is complete; record keeping is done above
    destroy_process(customer_pcb);
}

// =============================================================================
//  TELLER PROCESS — called when a service completion event fires for teller i
// =============================================================================
void teller_process(int teller_num)
{
    ProcessControlBlock *teller_pcb = teller_processes[teller_num];
    if (teller_pcb == nullptr) return;

    current_process = teller_pcb;

    // ── Is this teller's queue empty? ────────────────────────────────────────
    if (list_size[teller_num] == 0) {

        // Nobody waiting — remove busy token and go idle (wait in CES)
        list_remove(FIRST, num_tellers + teller_num);
        put_in_ces(teller_pcb);

    } else {

        // Pull the next customer from the head of the queue
        list_remove(FIRST, teller_num);

        // Record this customer's delay (current time − their arrival time)
        sampst(sim_time - transfer[1], SAMPST_DELAYS);

        // Schedule the next service completion for this teller
        transfer[3] = static_cast<float>(teller_num);
        event_schedule(sim_time + expon(mean_service, STREAM_SERVICE),
                       EVENT_SERVICE_DONE);

        // Teller remains busy — no state change needed
    }

    // After every service completion, check whether any customer should
    // jockey from a longer queue to this teller's (now shorter) queue
    jockey(teller_num);
}

// =============================================================================
//  JOCKEY — load-balance queues after a service completion at teller i
//
//  Rule: find the closest teller j (left-to-right tiebreak) whose total
//  count (queue + in-service) is at least 2 more than teller i's count.
//  Move that queue's last (tail) customer to teller i.
// =============================================================================
void jockey(int teller)
{
    int  jumper = 0;
    int  min_distance = 1000;
    int  ni = list_size[teller] + list_size[num_tellers + teller];

    for (int other = 1; other <= num_tellers; ++other) {
        if (other == teller) continue;
 
        int nj       = list_size[other] + list_size[num_tellers + other];
        int distance = abs(teller - other);

        // Jockey is worthwhile only if other queue is strictly longer by >1
        // and closer than any previously found candidate
        if (nj >= ni + 2 && distance < min_distance) {
            jumper       = other;
            min_distance = distance;
        }
    }

    if (jumper == 0) return;   // Nobody qualifies to jockey

    // Remove the last customer from jumper's queue
    list_remove(LAST, jumper);

    if (list_size[num_tellers + teller] > 0) {
        // Teller is still serving someone — place jockeying customer in queue
        list_file(LAST, teller);
    } else {
        // Teller is now idle — start serving the jockeying customer directly
        sampst(sim_time - transfer[1], SAMPST_DELAYS);

        // Mark teller busy
        list_file(FIRST, num_tellers + teller);

        // Reactivate teller from CES if it went idle
        ProcessControlBlock *t_pcb = teller_processes[teller];
        if (t_pcb != nullptr && t_pcb->state == PROCESS_CONDITIONAL)
            remove_from_ces(t_pcb);

        // Schedule new service completion
        transfer[3] = static_cast<float>(teller);
        event_schedule(sim_time + expon(mean_service, STREAM_SERVICE),
                       EVENT_SERVICE_DONE);
    }
}

// =============================================================================
//  FIND SHORTEST QUEUE — returns the leftmost teller with the fewest waiting
// =============================================================================
int find_shortest_queue()
{
    int best_len   = list_size[1];
    int best_teller = 1;

    for (int t = 2; t <= num_tellers; ++t) {
        if (list_size[t] < best_len) {
            best_len    = list_size[t];
            best_teller = t;
        }
    }
    return best_teller;
}

// =============================================================================
//  REPORT — print results for this teller configuration
// =============================================================================
void report()
{
    // Sum time-average queue lengths across all tellers
    float avg_in_queue = 0.0f;
    for (int t = 1; t <= num_tellers; ++t)
        avg_in_queue += filest(t);

    // Retrieve sampst summary: [1]=mean, [2]=count, [3]=max, [4]=min
    sampst(0.0f, -SAMPST_DELAYS);
    float avg_delay = transfer[1];
    float num_served = transfer[2];
    float max_delay  = transfer[3];

    // ── Console output ───────────────────────────────────────────────────────
    std::cout << "  Tellers = " << num_tellers << "\n"
              << "    Avg customers in queue : "
              << std::fixed << std::setprecision(3) << avg_in_queue << "\n"
              << "    Avg delay in queue     : "
              << std::setprecision(4) << avg_delay  << " min\n"
              << "    Max delay in queue     : "
              << max_delay  << " min\n"
              << "    Customers served       : "
              << static_cast<int>(num_served) << "\n\n";

    // ── File output ──────────────────────────────────────────────────────────
    fprintf(outfile,
            "\n\nWith %2d tellers:\n", num_tellers);
    fprintf(outfile,
            "  Time-avg customers in queue : %10.3f\n", avg_in_queue);
    fprintf(outfile,
            "  Average delay in queue      : %10.4f minutes\n", avg_delay);
    fprintf(outfile,
            "  Maximum delay in queue      : %10.4f minutes\n", max_delay);
    fprintf(outfile,
            "  Customers served            : %10d\n",
            static_cast<int>(num_served));

    // Full sampst table for the delay variable
    fprintf(outfile, "\nDelay statistics (sampst):\n");
    out_sampst(outfile, SAMPST_DELAYS, SAMPST_DELAYS);
}
