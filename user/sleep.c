#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  //law eli dakhel hagten w tany haga "?" yprint el help function
  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: sleep seconds\n");
    exit(0);
  }
  //law eli dakhel msh 2 yebaa feh ghalat el mafrod sleep w rakam bas
  if(argc != 2) {
    printf("Invalid command, you can only use a single number indicating seconds\n");
    exit(0);
  }
  //atoi ascii to integer
  //byhawel el string eli dakhel by default men argv[1] le integer alashan ne3raf ne3edo
  //law eli dakhel msh rakam byraga3 zero
  int sleeptime = atoi(argv[1]);
  //law eli dakhel msh rakam
  //bycheck law eli rage3 mn atoi howa zero w eli dakhel msh '0' maana keda eli dakhel msh rakam
  //strcmp byeraga3 zero law el two strings zay ba3d
 //fa law eli dakhel msh zero el strcmp hatraga3 rakam ghair zero
   if(argc == 2 && sleeptime < 0) {
    printf("Invalid command, you can only use a positive number indicating seconds\n");
    exit(0);
  }
  else if(argc==2 && sleeptime ==0 && strcmp(argv[1], "0")){
    printf("Invalid command, you can only use number indicating seconds, input is not a number\n");
    exit(0);
  }


  printf("Starting sleep for %d\n", sleeptime);
  sleep(sleeptime);
  printf("Finished sleeping...\n");

  exit(0);
}
