#include "kernel/types.h"
#include "user/user.h"

static void
usage(void)
{
  printf("Usage: tperf <num-procs> [work-ticks]\n");
  printf("  <num-procs>  : number of child processes to create (must be > 0)\n");
  printf("  [work-ticks]: optional ticks each child sleeps to accumulate time (default 5)\n");
  exit(1);
}

int
main(int argc, char *argv[])
{
  if(argc < 2 || argc > 3)
    usage();

  int nprocs = atoi(argv[1]);
  if(nprocs <= 0)
    usage();

  int work_ticks = (argc >= 3) ? atoi(argv[2]) : 5;
  if(work_ticks < 0)
    work_ticks = 0;

  printf("Spawning %d processes; each sleeps %d ticks\n", nprocs, work_ticks);

  for(int i = 0; i < nprocs; i++){
    int pid = fork();
    if(pid < 0){
      printf("fork failed at child %d\n", i);
      exit(1);
    }

    if(pid == 0){
      if(i % 2 == 0)
        sleep(1);

      for(int r = 0; r < work_ticks; r++)
        sleep(1);

      volatile int spin = 0;
      for(int j = 0; j < 10000; j++)
        spin += j;

      exit(0);
    }
  }

  for(int i = 0; i < nprocs; i++)
    wait(0);

  char *pmargv[] = {"perfmetrics", 0};
  if(exec("perfmetrics", pmargv) < 0){
    printf("Failed to exec perfmetrics\n");
    exit(1);
  }

  exit(0);
}
