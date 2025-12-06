#include "types.h"

struct perfmetrics {
    int num_processes;           // How many processes completed
    uint total_turnaround_time;  // Sum of all turnaround times
    uint total_waiting_time;     // Sum of all waiting times
    uint avg_turnaround_time;    // Average turnaround
    uint avg_waiting_time;       // Average waiting
};
