# Multi-Teller Bank Simulation — 2005076

## Problem Summary

A bank with **n tellers** (n = 4 to 7) opens for 8 hours.  
- Customers arrive with **exponential** interarrival times (mean 1 min → ~480 customers/day).  
- Service time per customer is **exponential** (mean 4.5 min).  
- Each teller has its **own queue**; a new customer joins the **shortest** (leftmost on tie).  
- After any service completion, **jockeying** may occur: if another teller's count (queue + in-service) is ≥ 2 more than the just-freed teller's count, the last customer in that longer queue moves over.

---

## Code Structure

| File | Role |
|---|---|
| `simlib.hpp` | Single header: all constants, structs, and function declarations |
| `simlib.cpp` | Three sections: LCG RNG, core simlib (lists/stats/events), process-support |
| `mtbank.cpp` | Simulation logic: main loop, customer, teller, jockey, report |

---

## Key Code Concepts

### Lists used by simlib

Simlib manages data through numbered **linked lists**.  
For `num_tellers = n`, the lists are mapped as:

| List number | Meaning |
|---|---|
| `1 … n` | Waiting queue for teller 1 … n |
| `n+1 … 2n` | "Busy" token for teller 1 … n (size = 1 if serving, 0 if idle) |
| `LIST_EVENT (25)` | Future Event Set — sorted by event time |
| `LIST_CES (21)` | Conditional Event Set — idle tellers waiting here |

### Why a "busy list" for each teller?

`list_size[n + teller]` is 1 when the teller is serving and 0 when idle.  
`filest(teller)` (time-average of `list_size[teller]`) gives the **time-average queue length** for that teller — summed across all tellers for the report.

### Jockeying condition

```cpp
if (nj >= ni + 2 && distance < min_distance)
```

`ni` = queue + busy count of the **freed** teller.  
`nj` = queue + busy count of the **candidate** teller.  
The gap must be ≥ 2 (not just 1) because moving 1 customer from a queue of 2 to a queue of 1 would just swap the imbalance.  
Among multiple candidates, the **closest** (then leftmost) wins.

### find_idle_teller vs find_shortest_queue

- `find_idle_teller` — scans left to right, returns the first teller whose busy list is empty **and** who is sitting in the CES.  
- `find_shortest_queue` — scans all teller queue lists, returns the one with the smallest `list_size` (leftmost on tie). Only called when **all** tellers are busy.

### Process Interaction paradigm

- **Teller process**: starts in the CES (idle). When activated by a customer or jockey, it serves, schedules a `SERVICE_DONE` event, and either goes back to CES (if queue empty) or dequeues the next customer.  
- **Customer process**: arrives, checks for an idle teller, either activates one (zero delay) or files itself in the shortest queue, then terminates.  
- The main loop is purely event-driven (`EVENT_ARRIVAL`, `EVENT_SERVICE_DONE`, `EVENT_CLOSE_DOORS`); the CES/FES mechanics simulate the *feel* of concurrent processes.

---

## Input Parameters and Their Effect on Output

Input file format: `min_tellers  max_tellers  mean_interarrival  mean_service  bank_hours`  
Example: `4 7 1.0 4.5 8.0`

---

### 1. `mean_interarrival` (default 1.0 min)

Traffic intensity per teller: $\rho = \frac{\text{mean\_service}}{\text{n} \times \text{mean\_interarrival}}$

| Change | Effect on output | Reason |
|---|---|---|
| **Increase** (arrivals slower) | Queue ↓, delay ↓, max delay ↓, customers served ↓ | Fewer customers per hour → less congestion |
| **Decrease** (arrivals faster) | Queue ↑, delay ↑, max delay ↑, customers served ↑ | More customers flood the tellers; queues build faster than they drain |

> Critical threshold: when $\rho \to 1$ (i.e., mean\_interarrival → mean\_service / n), queues explode. With n=4, threshold is 4.5/4 = 1.125 min — the default 1.0 is already over it, explaining the extreme n=4 results.

---

### 2. `mean_service` (default 4.5 min)

| Change | Effect on output | Reason |
|---|---|---|
| **Increase** | Queue ↑, delay ↑, max delay ↑, customers served ↓ | Tellers take longer → queue grows faster than it drains |
| **Decrease** | Queue ↓, delay ↓, max delay ↓, customers served ↑ | Faster service → queues clear quickly; more customers can be served before closing |

---

### 3. `min_tellers` / `max_tellers` (default 4 and 7)

These only control **which configurations are simulated** — they don't affect the results for any individual n.  
Increasing `min_tellers` or decreasing `max_tellers` just narrows the range of rows in the report.

For a **given n**, more tellers ↔ lower ρ per teller:

| n increases by 1 | Queue ↓↓, delay ↓↓ | Each teller handles fewer customers; jockeying also becomes nearly unnecessary |

---

### 4. `bank_hours` (default 8.0 hr)

| Change | Effect on output | Reason |
|---|---|---|
| **Increase** | Customers served ↑; queue/delay may increase or decrease | More customers arrive; if ρ < 1 system stays stable, if ρ > 1 queues keep growing so avg queue ↑ and avg delay ↑ |
| **Decrease** | Customers served ↓; queue ↓ for overloaded case | Fewer customers enter before doors close; queue has less time to build up |

> Note: simulation always drains completely after closing — customers who arrived before closing are all served. So `bank_hours` affects *how many enter*, not whether they are served.

---

## Quick Intuition Table

| Input ↑ | Avg queue | Avg delay | Max delay | Customers served |
|---|---|---|---|---|
| mean_interarrival | ↓ | ↓ | ↓ | ↓ |
| mean_service | ↑ | ↑ | ↑ | ↓ |
| n (tellers) | ↓ | ↓ | ↓ | ~ same |
| bank_hours | ↑ (if ρ>1) | ↑ (if ρ>1) | ↑ | ↑ |
