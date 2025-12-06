#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc != 2){
    printf("Usage: setsched <mode>\n");
    printf("Modes:\n");
    printf("  0 - Round Robin\n");
    printf("  1 - FCFS (First Come First Serve)\n");
    printf("  2 - Priority-Based\n");
    exit(1);
  }

  int mode = atoi(argv[1]);

  if(mode < 0 || mode > 2){
    printf("Invalid mode: %d\n", mode);
    printf("Valid modes: 0 (Round Robin), 1 (FCFS), 2 (Priority-Based)\n");
    exit(1);
  }

  if(setsched(mode) < 0){
    printf("Failed to set scheduler mode\n");
    exit(1);
  }

  char *mode_name;
  switch(mode){
    case 0: mode_name = "Round Robin"; break;
    case 1: mode_name = "FCFS"; break;
    case 2: mode_name = "Priority-Based"; break;
    default: mode_name = "Unknown"; break;
  }

  printf("Scheduler mode changed to: %s\n", mode_name);
  exit(0);
}
