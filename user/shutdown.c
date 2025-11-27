#include "kernel/types.h"
#include "user/user.h"

// Create the Functionality of the syscall
//mafihash haga tetshereh ya bashmohandes
int main() {

  printf("Shutting down bye bye...\n");
  sleep(10);
  shutdown();
  //optional salamo 3aleko
  exit(0);
}
