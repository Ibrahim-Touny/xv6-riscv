#include "kernel/types.h"
#include "user/user.h"

// Create the Functionality of the syscall
int main() {
  int random_number = random();
  printf("random number: %d\n", random_number);

  exit(0);
}
