#include "kernel/types.h"
#include "kernel/perfmetrics.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    struct perfmetrics pm;

    if(perfmetrics(&pm) < 0) {
        printf("Failed to get performance metrics\n");
        exit(1);
    }

    printf("Performance Metrics for a  total of %d processes:\n", pm.total_num_processes);

    if(pm.total_num_processes == 0) {
        printf("No completed processes to report metrics.\n");
    }
    else
    {
      if (pm.rr_num_processes > 0){
        printf("\nRound-Robin Scheduling:\n");
        printf("Completed Processes: %d\n", pm.rr_num_processes);
        printf("Average Turnaround Time: %d ticks\n", pm.rr_avg_turnaround_time);
        printf("Average Waiting Time: %d ticks\n", pm.rr_avg_waiting_time);
        printf("Total Turnaround Time: %d ticks\n", pm.rr_turnaround_time);
        printf("Total Waiting Time: %d ticks\n", pm.rr_waiting_time);
      }
      if (pm.fcfs_num_processes > 0){
        printf("\nFirst Come First Serve Scheduling:\n");
        printf("Completed Processes: %d\n", pm.fcfs_num_processes);
        printf("Average Turnaround Time: %d ticks\n", pm.fcfs_avg_turnaround_time);
        printf("Average Waiting Time: %d ticks\n", pm.fcfs_avg_waiting_time);
        printf("Total Turnaround Time: %d ticks\n", pm.fcfs_turnaround_time);
        printf("Total Waiting Time: %d ticks\n", pm.fcfs_waiting_time);
      }
      if (pm.pb_num_processes > 0){
        printf("\nPriority Based Scheduling:\n");
        printf("Completed Processes: %d\n", pm.pb_num_processes);
        printf("Average Turnaround Time: %d ticks\n", pm.pb_avg_turnaround_time);
        printf("Average Waiting Time: %d ticks\n", pm.pb_avg_waiting_time);
        printf("Total Turnaround Time: %d ticks\n", pm.pb_turnaround_time);
        printf("Total Waiting Time: %d ticks\n", pm.pb_waiting_time);
      }
    }

    exit(0);
}
