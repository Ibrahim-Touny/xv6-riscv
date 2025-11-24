#include "kernel/types.h"
#include "user/user.h"

// Create the Functionality of the syscall
int main() {
  int count = kbdint();
  printf("Keyboard interrupts since boot: %d\n", count);

  exit(0);
}
