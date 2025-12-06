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

    printf("=== Performance Metrics ===\n");
    printf("Completed Processes: %d\n", pm.num_processes);
    printf("Average Turnaround Time: %d ticks\n", pm.avg_turnaround_time);
    printf("Average Waiting Time: %d ticks\n", pm.avg_waiting_time);
    printf("Total Turnaround Time: %d ticks\n", pm.total_turnaround_time);
    printf("Total Waiting Time: %d ticks\n", pm.total_waiting_time);

    exit(0);
}
