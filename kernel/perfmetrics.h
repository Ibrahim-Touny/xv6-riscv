#include "types.h"

struct perfmetrics {
    int  total_num_processes;      // Total number of completed processes (all schedulers)

    int  rr_num_processes;         // Completed processes under Round-Robin
    uint rr_turnaround_time;       // Sum of RR turnaround times
    uint rr_waiting_time;          // Sum of RR waiting times
    uint rr_avg_turnaround_time;   // Average RR turnaround time
    uint rr_avg_waiting_time;      // Average RR waiting time

    int  fcfs_num_processes;       // Completed processes under FCFS
    uint fcfs_turnaround_time;     // Sum of FCFS turnaround times
    uint fcfs_waiting_time;        // Sum of FCFS waiting times
    uint fcfs_avg_turnaround_time; // Average FCFS turnaround time
    uint fcfs_avg_waiting_time;    // Average FCFS waiting time

    int  pb_num_processes;         // Completed processes under Priority-Based scheduling
    uint pb_turnaround_time;       // Sum of PB turnaround times
    uint pb_waiting_time;          // Sum of PB waiting times
    uint pb_avg_turnaround_time;   // Average PB turnaround time
    uint pb_avg_waiting_time;      // Average PB waiting time
};
