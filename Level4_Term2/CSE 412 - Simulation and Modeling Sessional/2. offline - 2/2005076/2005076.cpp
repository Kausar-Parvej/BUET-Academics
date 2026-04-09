#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lcgrand.h"

int amount, bigs, initial_inv_level, inv_level, next_event_type, num_events,
    num_months, num_values_demand, smalls;
float area_holding, area_shortage, holding_cost, incremental_cost, maxlag,
      mean_interdemand, minlag, prob_distrib_demand[26], setup_cost,
      shortage_cost, sim_time, time_last_event, time_next_event[5],
      total_ordering_cost;
FILE *infile, *outfile;

void initialize(void);
void timing(void);
void order_arrival(void);
void demand(void);
void evaluate(void);
void report(void);
void update_time_avg_stats(void);
float expon(float mean);
int random_integer(float prob_distrib[]);
float uniform(float a, float b);

int main() {
    int i, num_policies;
    
    infile = fopen("in.txt", "r");
    outfile = fopen("out.txt", "w");
    
    num_events = 4;
    
    fscanf(infile, "%d %d %d", &initial_inv_level, &num_months, &num_policies);
    fscanf(infile, "%d %f", &num_values_demand, &mean_interdemand);
    fscanf(infile, "%f %f %f %f", &setup_cost, &incremental_cost, &holding_cost, &shortage_cost);
    fscanf(infile, "%f %f", &minlag, &maxlag);
    
    for (i = 1; i <= num_values_demand; ++i)
        fscanf(infile, "%f", &prob_distrib_demand[i]);
    
    fprintf(outfile, "------Single-Product Inventory System------\n\n");
    fprintf(outfile, "Initial inventory level: %d items\n\n", initial_inv_level);
    fprintf(outfile, "Number of demand sizes: %d\n\n", num_values_demand);
    fprintf(outfile, "Distribution function of demand sizes:");
    for (i = 1; i <= num_values_demand; ++i)
        fprintf(outfile, " %.2f", prob_distrib_demand[i]);
    fprintf(outfile, " \n\n");
    fprintf(outfile, "Mean inter-demand time: %.2f months\n\n", mean_interdemand);
    fprintf(outfile, "Delivery lag range: %.2f to %.2f months\n\n", minlag, maxlag);
    fprintf(outfile, "Length of simulation: %d months\n\n", num_months);
    fprintf(outfile, "Costs:\n");
    fprintf(outfile, "K = %.2f\n", setup_cost);
    fprintf(outfile, "i = %.2f\n", incremental_cost);
    fprintf(outfile, "h = %.2f\n", holding_cost);
    fprintf(outfile, "pi = %.2f\n\n", shortage_cost);
    fprintf(outfile, "Number of policies: %d\n\n", num_policies);
    fprintf(outfile, "Policies:\n");
    fprintf(outfile, "----------------------------------------------------------------------------------------------------------\n");
    fprintf(outfile, " Policy          Avg_total_cost        Avg_ordering_cost        Avg_holding_cost       Avg_shortage_cost\n");
    fprintf(outfile, "----------------------------------------------------------------------------------------------------------\n");
    
    for (i = 1; i <= num_policies; ++i) {
        fscanf(infile, "%d %d", &smalls, &bigs);
        initialize();
        
        do {
            timing();
            update_time_avg_stats();
            
            switch (next_event_type) {
                case 1:
                    order_arrival();
                    break;
                case 2:
                    demand();
                    break;
                case 4:
                    evaluate();
                    break;
                case 3:
                    report();
                    break;
            }
        } while (next_event_type != 3);
    }
    
    fprintf(outfile, "\n-----------------------------------------------------------------------------------------------------------\n");
    
    fclose(infile);
    fclose(outfile);
    return 0;
}

void initialize(void) {
    sim_time = 0.0;
    inv_level = initial_inv_level;
    time_last_event = 0.0;
    total_ordering_cost = 0.0;
    area_holding = 0.0;
    area_shortage = 0.0;
    time_next_event[1] = 1.0e+30;
    time_next_event[2] = sim_time + expon(mean_interdemand);
    time_next_event[3] = num_months;
    time_next_event[4] = 0.0;
}

void timing(void) {
    int i;
    float min_time_next_event = 1.0e+29;
    next_event_type = 0;
    
    for (i = 1; i <= num_events; ++i) {
        if (time_next_event[i] < min_time_next_event) {
            min_time_next_event = time_next_event[i];
            next_event_type = i;
        }
    }
    
    if (next_event_type == 0) {
        fprintf(outfile, "\nEvent list empty at time %f", sim_time);
        exit(1);
    }
    
    sim_time = min_time_next_event;
}


void order_arrival(void) {
    inv_level += amount;
    time_next_event[1] = 1.0e+30;
}

void demand(void) {
    inv_level -= random_integer(prob_distrib_demand);
    time_next_event[2] = sim_time + expon(mean_interdemand);
}

void evaluate(void) {
    if (inv_level < smalls) {
        amount = bigs - inv_level;
        total_ordering_cost += setup_cost + incremental_cost * amount;
        time_next_event[1] = sim_time + uniform(minlag, maxlag);
    }
    time_next_event[4] = sim_time + 1.0;
}

void report(void) {
    float avg_holding_cost, avg_ordering_cost, avg_shortage_cost;
    avg_ordering_cost = total_ordering_cost / num_months;
    avg_holding_cost = holding_cost * area_holding / num_months;
    avg_shortage_cost = shortage_cost * area_shortage / num_months;
    fprintf(outfile, "\n(%3d,%3d)%20.2f%23.2f%25.2f%22.2f",
            smalls, bigs,
            avg_ordering_cost + avg_holding_cost + avg_shortage_cost,
            avg_ordering_cost, avg_holding_cost, avg_shortage_cost);
}

void update_time_avg_stats(void) {
    float time_since_last_event;
    time_since_last_event = sim_time - time_last_event;
    time_last_event = sim_time;
    
    if (inv_level < 0)
        area_shortage -= inv_level * time_since_last_event;
    else if (inv_level > 0)
        area_holding += inv_level * time_since_last_event;
}

float expon(float mean) {
    return -mean * log(lcgrand(1));
}

int random_integer(float prob_distrib[]) {
    int i;
    float u;
    u = lcgrand(1);
    for (i = 1; u >= prob_distrib[i]; ++i)
        ;
    return i;
}

float uniform(float a, float b) {
    return a + lcgrand(1) * (b - a);
}
