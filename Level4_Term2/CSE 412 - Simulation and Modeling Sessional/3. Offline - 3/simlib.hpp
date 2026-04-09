// =============================================================================
// simlib.hpp  —  Unified simulation-library header  (C++ edition)
//
// Merges the original simlibdefs.h, simlib.h, lcgrand.h and
// process_support.h into a single, self-contained header.
// =============================================================================

#pragma once

#include <cstdio>
#include <cstdlib>
#include <cmath>

// -----------------------------------------------------------------------------
//  SIMLIB DEFINITIONS  (from simlibdefs.h)
// -----------------------------------------------------------------------------

#define MAX_LIST  25        // Maximum number of lists
#define MAX_ATTR  10        // Maximum number of attributes per node
#define MAX_SVAR  25        // Maximum number of sampst variables
#define TIM_VAR   25        // Maximum number of timest variables
#define MAX_TVAR  50        // Maximum number of timest variables + lists
#define EPSILON   0.001     // Tolerance used inside event_cancel

// Array dimension constants (+1 because arrays are 1-indexed)
#define LIST_SIZE 26        // MAX_LIST + 1
#define ATTR_SIZE 11        // MAX_ATTR + 1
#define SVAR_SIZE 26        // MAX_SVAR + 1
#define TVAR_SIZE 51        // MAX_TVAR + 1

// Insertion / removal options for list_file and list_remove
#define FIRST      1        // Head of list
#define LAST       2        // Tail of list
#define INCREASING 3        // Sorted ascending by ranked attribute
#define DECREASING 4        // Sorted descending by ranked attribute

// Reserved list and special values
#define LIST_EVENT 25       // Simlib internal event list (ordered by time)
#define INF        1.0e30f  // Practical infinity

// Pre-defined attribute indices inside the transfer[] array for events
#define EVENT_TIME 1        // Attribute 1 holds the event time
#define EVENT_TYPE 2        // Attribute 2 holds the event type

// -----------------------------------------------------------------------------
//  PROCESS-SUPPORT DEFINITIONS  (from process_support.h)
// -----------------------------------------------------------------------------

#define MAX_TELLERS 10      // Upper limit on teller count

// Process execution states
#define PROCESS_ACTIVE      0   // Currently executing
#define PROCESS_SCHEDULED   1   // Waiting in Future Event Set (FES)
#define PROCESS_CONDITIONAL 2   // Waiting in Conditional Event Set (CES)
#define PROCESS_TERMINATED  3   // Execution complete

// Process-type tags
#define PROCESS_TYPE_CUSTOMER 1
#define PROCESS_TYPE_TELLER   2
#define PROCESS_TYPE_ARRIVAL  3

// Special list numbers used by the process-interaction layer
// (kept above the highest queue/busy list, which is 2*MAX_TELLERS = 20)
#define LIST_CES         (2 * MAX_TELLERS + 1)  // Conditional Event Set list
#define LIST_PROCESS_FES (2 * MAX_TELLERS + 2)  // Process-oriented FES list

// -----------------------------------------------------------------------------
//  PROCESS CONTROL BLOCK
// -----------------------------------------------------------------------------

struct ProcessControlBlock {
    int   process_id;           // Unique ID assigned at creation
    int   process_type;         // One of PROCESS_TYPE_*
    int   state;                // One of PROCESS_ACTIVE / SCHEDULED / ...
    float reactivation_time;    // Next scheduled wakeup time
    int   teller_number;        // Teller index (teller processes only)
    float arrival_time;         // Arrival timestamp (customer processes only)
    int   assigned_teller;      // Teller serving this customer
    int   resume_point;         // Continuation label (process-split point)
};

// -----------------------------------------------------------------------------
//  SIMLIB INTERNAL LINKED-LIST NODE
// -----------------------------------------------------------------------------

struct master {
    float         *value;   // Attribute array for this node
    struct master *pr;      // Previous node
    struct master *sr;      // Successor (next) node
};

// -----------------------------------------------------------------------------
//  SIMLIB GLOBAL VARIABLES  (defined in simlib.cpp, declared here)
// -----------------------------------------------------------------------------

extern int     *list_rank;      // Rank attribute for sorted lists
extern int     *list_size;      // Current length of each list
extern int      next_event_type;// Type of the most recently processed event
extern int      maxatr;         // Maximum attribute count (user-settable)
extern int      maxlist;        // Maximum list count (user-settable)

extern float   *transfer;       // Shared attribute-transfer buffer
extern float    sim_time;       // Current simulation clock
extern float    prob_distrib[26]; // Scratch array for random_integer()

extern master **head;           // Head pointers for all lists
extern master **tail;           // Tail pointers for all lists

// -----------------------------------------------------------------------------
//  SIMLIB FUNCTION DECLARATIONS
// -----------------------------------------------------------------------------

void  init_simlib();
void  list_file(int option, int list);
void  list_remove(int option, int list);
void  timing();
void  event_schedule(float time_of_event, int type_of_event);
int   event_cancel(int event_type);
float sampst(float value, int varibl);
float timest(float value, int varibl);
float filest(int list);
void  out_sampst(FILE *unit, int lowvar, int highvar);
void  out_timest(FILE *unit, int lowvar, int highvar);
void  out_filest(FILE *unit, int lowlist, int highlist);
float expon(float mean, int stream);
int   random_integer(float prob_distrib_arr[], int stream);
float uniform(float a, float b, int stream);
float erlang(int m, float mean, int stream);
float lcgrand(int stream);
void  lcgrandst(long zset, int stream);
long  lcgrandgt(int stream);

// -----------------------------------------------------------------------------
//  PROCESS-SUPPORT GLOBAL VARIABLES  (defined in simlib.cpp)
// -----------------------------------------------------------------------------

extern ProcessControlBlock *current_process;
extern ProcessControlBlock *process_table[1000]; // Supports up to 1000 PCBs
extern int                  next_process_id;
extern int                  num_active_processes;

// -----------------------------------------------------------------------------
//  PROCESS-SUPPORT FUNCTION DECLARATIONS
// -----------------------------------------------------------------------------

void                 init_process_system();
ProcessControlBlock *create_process(int type, int teller_num);
void                 destroy_process(ProcessControlBlock *pcb);
void                 schedule_process(ProcessControlBlock *pcb, float time);
void                 activate_process_now(ProcessControlBlock *pcb);
void                 wait_for_time(float duration);
void                 wait_conditional();
ProcessControlBlock *find_idle_teller(int num_tellers_arg);
ProcessControlBlock *get_teller_process(int teller_num);
void                 put_in_ces(ProcessControlBlock *pcb);
void                 remove_from_ces(ProcessControlBlock *pcb);
