#include "kernel/types.h"
#include "user/user.h"
#include "kernel/ptable.h"

char* state2str(int s) {
  switch(s) {
    case 0:  return "UNUSED";
    case 1:  return "USED";
    case 2:  return "SLEEPING";
    case 3:  return "RUNNABLE";
    case 4:  return "RUNNING";
    case 5:  return "ZOMBIE";
    default: return "UNKNOWN";
  }
}

int
main(int argc, char *argv[])
{
  struct ptable pt[64];   // buffer for 64 processes
  int n = 64;

  int myppid = getppid();
  printf("Current process PPID = %d\n\n", myppid);

  if(getptable(n, (char*)pt) != 1){
    printf("getptable failed!\n");
    exit(1);
  }

  printf("PID\tPPID\tSIZE\tNAME\tSTATE\n");

  for(int i = 0; i < n; i++) {
    if(pt[i].pid == 0)
      break;

    char* state_str = state2str(pt[i].state);

    printf("%d\t", pt[i].pid);
    printf("%d\t", pt[i].ppid);
    printf("%lu\t", (unsigned long)pt[i].sz);
    printf("%s\t", pt[i].name);
    printf("%s\n", state_str);
  }

  exit(0);
}
