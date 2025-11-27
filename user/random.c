#include "kernel/types.h"
#include "user/user.h"

// Create the Functionality of the syscall
int main() {
  int random = kbdint();
  printf("random number: %d\n", random);

  exit(0);
}
