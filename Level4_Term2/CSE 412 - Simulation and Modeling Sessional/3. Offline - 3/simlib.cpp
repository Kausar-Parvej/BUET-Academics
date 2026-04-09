// =============================================================================
// simlib.cpp  —  Simulation library implementation  (C++ edition)
//
// Contains three logical sections:
//   1. LCG random-number generator   (from lcgrand.h)
//   2. Core simlib routines          (from simlib.c)
//   3. Process-interaction helpers   (from process_support.c)
// =============================================================================

#include "simlib.hpp"

// =============================================================================
//  SECTION 1 — LCG RANDOM-NUMBER GENERATOR  (adapted from lcgrand.h)
//
//  Prime-modulus multiplicative linear congruential generator.
//  Z[i] = (630360016 * Z[i-1])  mod (2^31 - 1)
//  100 independent streams are provided; seeds are spaced 100,000 apart.
// =============================================================================

#define MODLUS 2147483647L
#define MULT1  24112L
#define MULT2  26143L

// Default seeds for streams 0 … 99
static long zrng[] = {
              1L,
 1973272912L,  281629770L,   20006270L, 1280689831L, 2096730329L,
 1933576050L,  913566091L,  246780520L, 1363774876L,  604901985L,
 1511192140L, 1259851944L,  824064364L,  150493284L,  242708531L,
   75253171L, 1964472944L, 1202299975L,  233217322L, 1911216000L,
  726370533L,  403498145L,  993232223L, 1103205531L,  762430696L,
 1922803170L, 1385516923L,   76271663L,  413682397L,  726466604L,
  336157058L, 1432650381L, 1120463904L,  595778810L,  877722890L,
 1046574445L,   68911991L, 2088367019L,  748545416L,  622401386L,
 2122378830L,  640690903L, 1774806513L, 2132545692L, 2079249579L,
   78130110L,  852776735L, 1187867272L, 1351423507L, 1645973084L,
 1997049139L,  922510944L, 2045512870L,  898585771L,  243649545L,
 1004818771L,  773686062L,  403188473L,  372279877L, 1901633463L,
  498067494L, 2087759558L,  493157915L,  597104727L, 1530940798L,
 1814496276L,  536444882L, 1663153658L,  855503735L,   67784357L,
 1432404475L,  619691088L,  119025595L,  880802310L,  176192644L,
 1116780070L,  277854671L, 1366580350L, 1142483975L, 2026948561L,
 1053920743L,  786262391L, 1792203830L, 1494667770L, 1923011392L,
 1433700034L, 1244184613L, 1147297105L,  539712780L, 1545929719L,
  190641742L, 1645390429L,  264907697L,  620389253L, 1502074852L,
  927711160L,  364849192L, 2049576050L,  638580085L,  547070247L
};

// Returns the next U(0,1) random variate from the given stream.
float lcgrand(int stream)
{
    long zi, lowprd, hi31;

    zi     = zrng[stream];
    lowprd = (zi & 65535L) * MULT1;
    hi31   = (zi >> 16)    * MULT1 + (lowprd >> 16);
    zi     = ((lowprd & 65535L) - MODLUS)
           + ((hi31  & 32767L) << 16)
           + ( hi31 >> 15);
    if (zi < 0) zi += MODLUS;

    lowprd = (zi & 65535L) * MULT2;
    hi31   = (zi >> 16)    * MULT2 + (lowprd >> 16);
    zi     = ((lowprd & 65535L) - MODLUS)
           + ((hi31  & 32767L) << 16)
           + ( hi31 >> 15);
    if (zi < 0) zi += MODLUS;

    zrng[stream] = zi;
    return static_cast<float>(zi >> 7 | 1) / 16777216.0f;
}

// Sets the seed for the given stream.
void lcgrandst(long zset, int stream)
{
    zrng[stream] = zset;
}

// Returns the current seed for the given stream.
long lcgrandgt(int stream)
{
    return zrng[stream];
}


// =============================================================================
//  SECTION 2 — CORE SIMLIB ROUTINES  (adapted from simlib.c)
// =============================================================================

// ── Global variable definitions ──────────────────────────────────────────────

int     *list_rank       = nullptr;
int     *list_size       = nullptr;
int      next_event_type = 0;
int      maxatr          = 0;
int      maxlist         = 0;

float   *transfer        = nullptr;
float    sim_time        = 0.0f;
float    prob_distrib[26];

master **head            = nullptr;
master **tail            = nullptr;

// ── Forward declarations for internal helper ─────────────────────────────────

static void pprint_out(FILE *unit, int i);

// ── init_simlib ───────────────────────────────────────────────────────────────
// Must be called from main before any simulation activity.
// LIST_EVENT (25) is reserved for the event list and is always sorted by
// event time.
void init_simlib()
{
    int list;
    int listsize;

    if (maxlist < 1) maxlist = MAX_LIST;
    listsize = maxlist + 1;

    sim_time = 0.0f;
    if (maxatr < 4) maxatr = MAX_ATTR;

    // Allocate list-management arrays
    list_rank = static_cast<int *>   (calloc(listsize, sizeof(int)));
    list_size = static_cast<int *>   (calloc(listsize, sizeof(int)));
    head      = static_cast<master **>(calloc(listsize, sizeof(master *)));
    tail      = static_cast<master **>(calloc(listsize, sizeof(master *)));
    transfer  = static_cast<float *> (calloc(maxatr + 1, sizeof(float)));

    for (list = 1; list <= maxlist; ++list) {
        head[list]      = nullptr;
        tail[list]      = nullptr;
        list_size[list] = 0;
        list_rank[list] = 0;
    }

    // Event list sorted in increasing order of event time (attribute 1)
    list_rank[LIST_EVENT] = EVENT_TIME;

    // Reset statistical accumulators
    sampst(0.0f, 0);
    timest(0.0f, 0);
}

// ── list_file ─────────────────────────────────────────────────────────────────
// Insert the current transfer[] record into the specified list.
// option = FIRST | LAST | INCREASING | DECREASING
void list_file(int option, int list)
{
    master *row, *ahead, *behind, *ihead, *itail;
    int     item, postest;

    if (list < 0 || list > MAX_LIST) {
        printf("\nInvalid list %d for list_file at time %f\n", list, sim_time);
        exit(1);
    }

    ++list_size[list];

    if (option < 1 || option > DECREASING) {
        printf("\n%d is an invalid option for list_file on list %d at time %f\n",
               option, list, sim_time);
        exit(1);
    }

    if (list_size[list] == 1) {
        // First node in the list
        row         = static_cast<master *>(malloc(sizeof(master)));
        head[list]  = row;
        tail[list]  = row;
        row->pr     = nullptr;
        row->sr     = nullptr;
    } else {
        // List already has nodes — determine insertion position
        if (option == INCREASING || option == DECREASING) {
            item = list_rank[list];
            if (item < 1 || item > maxatr) {
                printf("%d is an improper rank for list %d at time %f\n",
                       item, list, sim_time);
                exit(1);
            }
            row    = head[list];
            behind = nullptr;

            if (option == INCREASING) {
                postest = (transfer[item] >= row->value[item]);
                while (postest) {
                    behind  = row;
                    row     = row->sr;
                    postest = (behind != tail[list]);
                    if (postest)
                        postest = (transfer[item] >= row->value[item]);
                }
            } else {
                postest = (transfer[item] <= row->value[item]);
                while (postest) {
                    behind  = row;
                    row     = row->sr;
                    postest = (behind != tail[list]);
                    if (postest)
                        postest = (transfer[item] <= row->value[item]);
                }
            }

            if      (row == head[list])    option = FIRST;
            else if (behind == tail[list]) option = LAST;
            else {
                // Insert in the interior of the list
                ahead       = behind->sr;
                row         = static_cast<master *>(malloc(sizeof(master)));
                row->pr     = behind;
                behind->sr  = row;
                ahead->pr   = row;
                row->sr     = ahead;
            }
        }

        if (option == FIRST) {
            row         = static_cast<master *>(malloc(sizeof(master)));
            ihead       = head[list];
            ihead->pr   = row;
            row->sr     = ihead;
            row->pr     = nullptr;
            head[list]  = row;
        }
        if (option == LAST) {
            row         = static_cast<master *>(malloc(sizeof(master)));
            itail       = tail[list];
            row->pr     = itail;
            itail->sr   = row;
            row->sr     = nullptr;
            tail[list]  = row;
        }
    }

    // Copy transfer[] into the new node
    row->value = static_cast<float *>(calloc(maxatr + 1, sizeof(float)));
    for (item = 0; item <= maxatr; ++item)
        row->value[item] = transfer[item];

    // Update time-average statistics for this list
    timest(static_cast<float>(list_size[list]), TIM_VAR + list);
}

// ── list_remove ───────────────────────────────────────────────────────────────
// Remove a record from the list and place its attributes in transfer[].
// option = FIRST | LAST
void list_remove(int option, int list)
{
    master *row, *ihead, *itail;

    if (list < 0 || list > MAX_LIST) {
        printf("\nInvalid list %d for list_remove at time %f\n", list, sim_time);
        exit(1);
    }
    if (list_size[list] <= 0) {
        printf("\nUnderflow of list %d at time %f\n", list, sim_time);
        exit(1);
    }
    if (option != FIRST && option != LAST) {
        printf("\n%d is an invalid option for list_remove on list %d at time %f\n",
               option, list, sim_time);
        exit(1);
    }

    --list_size[list];

    if (list_size[list] == 0) {
        // Only one record existed — remove it directly
        row        = head[list];
        head[list] = nullptr;
        tail[list] = nullptr;
    } else {
        switch (option) {
            case FIRST:
                row        = head[list];
                ihead      = row->sr;
                ihead->pr  = nullptr;
                head[list] = ihead;
                break;
            case LAST:
                row        = tail[list];
                itail      = row->pr;
                itail->sr  = nullptr;
                tail[list] = itail;
                break;
        }
    }

    // Hand ownership of the value array to transfer[]
    free(static_cast<void *>(transfer));
    transfer = row->value;
    free(static_cast<void *>(row));

    timest(static_cast<float>(list_size[list]), TIM_VAR + list);
}

// ── timing ────────────────────────────────────────────────────────────────────
// Advance the simulation clock to the next scheduled event.
void timing()
{
    list_remove(FIRST, LIST_EVENT);

    if (transfer[EVENT_TIME] < sim_time) {
        printf("\nTime reversal: event type %g at time %g (current time %f)\n",
               transfer[EVENT_TYPE], transfer[EVENT_TIME], sim_time);
        exit(1);
    }

    sim_time         = transfer[EVENT_TIME];
    next_event_type  = static_cast<int>(transfer[EVENT_TYPE]);
}

// ── event_schedule ─────────────────────────────────────────────────────────────
// Schedule a future event.  Any extra attributes beyond [1] and [2] should
// already be set in transfer[] by the caller before invoking this function.
void event_schedule(float time_of_event, int type_of_event)
{
    transfer[EVENT_TIME] = time_of_event;
    transfer[EVENT_TYPE] = static_cast<float>(type_of_event);
    list_file(INCREASING, LIST_EVENT);
}

// ── event_cancel ──────────────────────────────────────────────────────────────
// Remove the first occurrence of an event of the given type from the event
// list.  Returns 1 if an event was cancelled, 0 otherwise.
int event_cancel(int event_type)
{
    master *row, *ahead, *behind;
    float   high, low, value;

    if (list_size[LIST_EVENT] == 0) return 0;

    row   = head[LIST_EVENT];
    low   = static_cast<float>(event_type) - EPSILON;
    high  = static_cast<float>(event_type) + EPSILON;
    value = row->value[EVENT_TYPE];

    while ((value <= low || value >= high) && row != tail[LIST_EVENT]) {
        row   = row->sr;
        value = row->value[EVENT_TYPE];
    }

    if (row == tail[LIST_EVENT]) {
        if (value > low && value < high) {
            list_remove(LAST, LIST_EVENT);
            return 1;
        }
        return 0;
    }

    if (row == head[LIST_EVENT]) {
        list_remove(FIRST, LIST_EVENT);
        return 1;
    }

    // Remove from interior
    ahead           = row->sr;
    behind          = row->pr;
    behind->sr      = ahead;
    ahead->pr       = behind;
    --list_size[LIST_EVENT];

    free(static_cast<void *>(transfer));
    transfer = row->value;
    free(static_cast<void *>(row));

    timest(static_cast<float>(list_size[LIST_EVENT]), TIM_VAR + LIST_EVENT);
    return 1;
}

// ── sampst ────────────────────────────────────────────────────────────────────
// Accumulate or report discrete-time statistics.
//   variable == 0  → initialise all accumulators
//   variable  > 0  → record a new observation
//   variable  < 0  → write report for |variable| into transfer[1..4]
float sampst(float value, int variable)
{
    static int   num_obs[SVAR_SIZE];
    static float vmax[SVAR_SIZE], vmin[SVAR_SIZE], vsum[SVAR_SIZE];
    int ivar;

    if (variable > 0) {
        vsum[variable] += value;
        if (value > vmax[variable]) vmax[variable] = value;
        if (value < vmin[variable]) vmin[variable] = value;
        ++num_obs[variable];
        return 0.0f;
    }
    if (variable < 0) {
        ivar         = -variable;
        transfer[2]  = static_cast<float>(num_obs[ivar]);
        transfer[3]  = vmax[ivar];
        transfer[4]  = vmin[ivar];
        transfer[1]  = (num_obs[ivar] == 0)
                       ? 0.0f
                       : vsum[ivar] / transfer[2];
        return transfer[1];
    }
    // Initialise
    for (ivar = 1; ivar <= MAX_SVAR; ++ivar) {
        vsum[ivar]   = 0.0f;
        vmax[ivar]   = -static_cast<float>(INF);
        vmin[ivar]   =  static_cast<float>(INF);
        num_obs[ivar] = 0;
    }
    return 0.0f;
}

// ── timest ────────────────────────────────────────────────────────────────────
// Accumulate or report continuous-time statistics.
//   variable == 0  → initialise all accumulators
//   variable  > 0  → update area and extremes with new level
//   variable  < 0  → write report for |variable| into transfer[1..3]
float timest(float value, int variable)
{
    static float area[TVAR_SIZE], tmax[TVAR_SIZE], tmin[TVAR_SIZE],
                 preval[TVAR_SIZE], tlvc[TVAR_SIZE], treset;
    int ivar;

    if (variable > 0) {
        area[variable] += (sim_time - tlvc[variable]) * preval[variable];
        if (value > tmax[variable]) tmax[variable] = value;
        if (value < tmin[variable]) tmin[variable] = value;
        preval[variable] = value;
        tlvc[variable]   = sim_time;
        return 0.0f;
    }
    if (variable < 0) {
        ivar            = -variable;
        area[ivar]     += (sim_time - tlvc[ivar]) * preval[ivar];
        tlvc[ivar]      = sim_time;
        transfer[1]     = area[ivar] / (sim_time - treset);
        transfer[2]     = tmax[ivar];
        transfer[3]     = tmin[ivar];
        return transfer[1];
    }
    // Initialise
    for (ivar = 1; ivar <= MAX_TVAR; ++ivar) {
        area[ivar]   = 0.0f;
        tmax[ivar]   = -static_cast<float>(INF);
        tmin[ivar]   =  static_cast<float>(INF);
        preval[ivar] = 0.0f;
        tlvc[ivar]   = sim_time;
    }
    treset = sim_time;
    return 0.0f;
}

// ── filest ────────────────────────────────────────────────────────────────────
// Report time-average statistics for a given list (delegates to timest).
float filest(int list)
{
    return timest(0.0f, -(TIM_VAR + list));
}

// ── pprint_out ────────────────────────────────────────────────────────────────
// Write the i-th transfer[] value to the given file, replacing sentinel ±1e30
// with 0 for readability.
static void pprint_out(FILE *unit, int i)
{
    float v = transfer[i];
    if (v == -1.0e30f || v == 1.0e30f) v = 0.0f;
    fprintf(unit, " %#15.6G ", v);
}

// ── out_sampst ────────────────────────────────────────────────────────────────
void out_sampst(FILE *unit, int lowvar, int highvar)
{
    if (lowvar > highvar || lowvar > MAX_SVAR || highvar > MAX_SVAR) return;

    fprintf(unit, "\n sampst                         Number");
    fprintf(unit, "\nvariable                          of");
    fprintf(unit, "\n number       Average           values          Maximum");
    fprintf(unit, "          Minimum");
    fprintf(unit, "\n___________________________________");
    fprintf(unit, "_____________________________________");

    for (int ivar = lowvar; ivar <= highvar; ++ivar) {
        fprintf(unit, "\n\n%5d", ivar);
        sampst(0.0f, -ivar);
        for (int iatrr = 1; iatrr <= 4; ++iatrr)
            pprint_out(unit, iatrr);
    }

    fprintf(unit, "\n___________________________________");
    fprintf(unit, "_____________________________________\n\n\n");
}

// ── out_timest ────────────────────────────────────────────────────────────────
void out_timest(FILE *unit, int lowvar, int highvar)
{
    if (lowvar > highvar || lowvar > TIM_VAR || highvar > TIM_VAR) return;

    fprintf(unit, "\n  timest");
    fprintf(unit, "\n variable       Time");
    fprintf(unit, "\n  number       average          Maximum          Minimum");
    fprintf(unit, "\n________________________________________________________");

    for (int ivar = lowvar; ivar <= highvar; ++ivar) {
        fprintf(unit, "\n\n%5d", ivar);
        timest(0.0f, -ivar);
        for (int iatrr = 1; iatrr <= 3; ++iatrr)
            pprint_out(unit, iatrr);
    }

    fprintf(unit, "\n________________________________________________________\n\n\n");
}

// ── out_filest ────────────────────────────────────────────────────────────────
void out_filest(FILE *unit, int lowlist, int highlist)
{
    if (lowlist > highlist || lowlist > MAX_LIST || highlist > MAX_LIST) return;

    fprintf(unit, "\n  File         Time");
    fprintf(unit, "\n number       average          Maximum          Minimum");
    fprintf(unit, "\n_______________________________________________________");

    for (int list = lowlist; list <= highlist; ++list) {
        fprintf(unit, "\n\n%5d", list);
        filest(list);
        for (int iatrr = 1; iatrr <= 3; ++iatrr)
            pprint_out(unit, iatrr);
    }

    fprintf(unit, "\n_______________________________________________________\n\n\n");
}

// ── Statistical distribution variate generators ───────────────────────────────

float expon(float mean, int stream)
{
    return -mean * std::log(lcgrand(stream));
}

int random_integer(float prob_distrib_arr[], int stream)
{
    float u = lcgrand(stream);
    int   i = 1;
    while (u >= prob_distrib_arr[i]) ++i;
    return i;
}

float uniform(float a, float b, int stream)
{
    return a + lcgrand(stream) * (b - a);
}

float erlang(int m, float mean, int stream)
{
    float mean_exp = mean / static_cast<float>(m);
    float sum      = 0.0f;
    for (int i = 1; i <= m; ++i)
        sum += expon(mean_exp, stream);
    return sum;
}


// =============================================================================
//  SECTION 3 — PROCESS-INTERACTION SUPPORT  (adapted from process_support.c)
// =============================================================================

// ── Global process-management definitions ─────────────────────────────────────

ProcessControlBlock *current_process      = nullptr;
ProcessControlBlock *process_table[1000];   // Registered PCBs by ID
int                  next_process_id      = 0;
int                  num_active_processes = 0;

// ── init_process_system ───────────────────────────────────────────────────────
// Reset all process-management state.  Call once per simulation run.
void init_process_system()
{
    next_process_id      = 0;
    num_active_processes = 0;
    current_process      = nullptr;

    for (int i = 0; i < 1000; ++i)
        process_table[i] = nullptr;
}

// ── create_process ────────────────────────────────────────────────────────────
// Allocate and initialise a new Process Control Block.
ProcessControlBlock *create_process(int type, int teller_num)
{
    ProcessControlBlock *pcb =
        static_cast<ProcessControlBlock *>(malloc(sizeof(ProcessControlBlock)));

    if (pcb == nullptr) {
        fprintf(stderr, "Error: cannot allocate ProcessControlBlock.\n");
        exit(1);
    }

    pcb->process_id         = next_process_id++;
    pcb->process_type       = type;
    pcb->state              = PROCESS_ACTIVE;
    pcb->reactivation_time  = 0.0f;
    pcb->teller_number      = teller_num;
    pcb->arrival_time       = 0.0f;
    pcb->assigned_teller    = 0;
    pcb->resume_point       = 0;

    process_table[pcb->process_id] = pcb;
    ++num_active_processes;

    return pcb;
}

// ── destroy_process ───────────────────────────────────────────────────────────
// Mark a PCB as terminated, remove it from the table, and free memory.
void destroy_process(ProcessControlBlock *pcb)
{
    if (pcb == nullptr) return;

    pcb->state                          = PROCESS_TERMINATED;
    process_table[pcb->process_id]      = nullptr;
    --num_active_processes;
    free(static_cast<void *>(pcb));
}

// ── schedule_process ──────────────────────────────────────────────────────────
// Mark the process as scheduled and put it in the FES at the given time.
void schedule_process(ProcessControlBlock *pcb, float time)
{
    pcb->state              = PROCESS_SCHEDULED;
    pcb->reactivation_time  = time;
    transfer[1] = static_cast<float>(pcb->process_id);
    transfer[2] = static_cast<float>(pcb->process_type);
    transfer[3] = static_cast<float>(pcb->teller_number);
    event_schedule(time, pcb->process_type);
}

// ── activate_process_now ─────────────────────────────────────────────────────
// Place a process in the Conditional Event Set for immediate activation.
void activate_process_now(ProcessControlBlock *pcb)
{
    pcb->state  = PROCESS_ACTIVE;
    transfer[1] = static_cast<float>(pcb->process_id);
    transfer[2] = static_cast<float>(pcb->process_type);
    transfer[3] = static_cast<float>(pcb->teller_number);
    list_file(LAST, LIST_CES);
}

// ── wait_for_time ─────────────────────────────────────────────────────────────
// Schedule the current process to resume after a simulated time interval.
void wait_for_time(float duration)
{
    if (current_process != nullptr)
        schedule_process(current_process, sim_time + duration);
}

// ── wait_conditional ─────────────────────────────────────────────────────────
// Suspend the current process in the CES until explicitly activated.
void wait_conditional()
{
    if (current_process != nullptr)
        put_in_ces(current_process);
}

// ── put_in_ces ────────────────────────────────────────────────────────────────
// Move a process into the Conditional Event Set (teller waiting for customer).
void put_in_ces(ProcessControlBlock *pcb)
{
    pcb->state  = PROCESS_CONDITIONAL;
    transfer[1] = static_cast<float>(pcb->process_id);
    transfer[2] = static_cast<float>(pcb->process_type);
    transfer[3] = static_cast<float>(pcb->teller_number);
    list_file(LAST, LIST_CES);
}

// ── remove_from_ces ───────────────────────────────────────────────────────────
// Scan the CES, find the PCB with the matching process_id, and remove it.
// All other CES entries are preserved (extracted and re-filed).
void remove_from_ces(ProcessControlBlock *pcb)
{
    int  sz    = list_size[LIST_CES];
    bool found = false;

    for (int i = 0; i < sz; ++i) {
        list_remove(FIRST, LIST_CES);

        if (static_cast<int>(transfer[1]) == pcb->process_id) {
            found = true;
            break;
        }
        // Not a match — put it back at the tail
        list_file(LAST, LIST_CES);
    }

    if (found)
        pcb->state = PROCESS_ACTIVE;
}

// ── find_idle_teller ─────────────────────────────────────────────────────────
// Scan tellers 1 … num_tellers_arg (left to right).  Return the PCB of the
// first idle teller found (queue empty, not currently serving, and in CES).
// Returns nullptr if all tellers are busy.
ProcessControlBlock *find_idle_teller(int num_tellers_arg)
{
    for (int teller = 1; teller <= num_tellers_arg; ++teller) {
        // Teller is idle when its queue list AND its busy list are both empty
        if (list_size[teller] == 0 &&
            list_size[num_tellers_arg + teller] == 0)
        {
            ProcessControlBlock *t_pcb = get_teller_process(teller);
            if (t_pcb != nullptr && t_pcb->state == PROCESS_CONDITIONAL)
                return t_pcb;
        }
    }
    return nullptr;
}

// ── get_teller_process ────────────────────────────────────────────────────────
// Look up the PCB for a specific teller by teller number.
ProcessControlBlock *get_teller_process(int teller_num)
{
    for (int i = 0; i < next_process_id; ++i) {
        ProcessControlBlock *p = process_table[i];
        if (p != nullptr
            && p->process_type  == PROCESS_TYPE_TELLER
            && p->teller_number == teller_num)
        {
            return p;
        }
    }
    return nullptr;
}
