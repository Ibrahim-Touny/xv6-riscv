#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  //law eli dakhel hagten w tany haga "?" yprint el help function
  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: sleep milli seconds\n");
    exit(0);
  }
  //law eli dakhel msh 2 yebaa feh ghalat el mafrod sleep w rakam bas
  if(argc != 2) {
    printf("Invalid command, you can only use a single number indicating milli seconds\n");
    exit(0);
  }
  //atoi ascii to integer
  //byhawel el string eli dakhel by default men argv[1] le integer alashan ne3raf ne3edo
  //law eli dakhel msh rakam byraga3 zero
  int sleeptime = atoi(argv[1]);
  //bycheck law eli rage3 mn atoi howa zero w eli dakhel msh '0' maana keda eli dakhel msh rakam
  //strcmp byeraga3 zero law el two strings zay ba3d
 //fa law eli dakhel msh zero el strcmp hatraga3 rakam ghair zero
  if(argc==2 && sleeptime ==0 && strcmp(argv[1], "0")){
    printf("Invalid command, you can only use number indicating milli seconds, input is not a positive number\n");
    exit(0);
  }

  printf("Starting sleep for %d\n", sleeptime);
  //byndah system call sleep w byeb3atlo el sleeptime eli howa el number eli dakhelna alashan ysleep milli seconds
  sleep(sleeptime);
  printf("Finished sleeping\n");

  exit(0);
}
