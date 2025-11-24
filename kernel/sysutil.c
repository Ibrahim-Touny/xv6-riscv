// Create new sysutil file for system utilities
// functions could have been added to other sys files but here better for clarity
#include "types.h"

// variable to hold keyboard interrupt count
extern int kbd_intr_count;

// Create system call for keyboard interrupt count
uint64 sys_kbdint(void)
{
  return kbd_intr_count;
}
