// Create new sysutil file for system utilities
// functions could have been added to other sys files but here better for clarity
#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "syscall.h"
#include "defs.h"
// variable to hold keyboard interrupt count
extern int kbd_intr_count;

// Create system call for keyboard interrupt count
uint64 sys_kbdint(void)
{
  return kbd_intr_count;
}

//dh el start bta3 el random number generator
static unsigned int rand_seed = 1;

uint64 sys_random(void)
{
    // LCG algorithm eli ibrahim sherif talabo
    // Formula: Xn+1 = (a * Xn + c) mod m
    //el a wl c wl m deh constants ma3rofa lel LCG
    //hna estakhdemna 2^31 as m
    //el ar dh el rakam eli byhaded el randomness bta3et el rkam kol ma keber el circle of randomness betekbar
    //el c dh el increment byzawed 3ala el value kol marra 3ashan mayeb2ash nafs el value w alshan yprevent en el arkam tebaa sequential
    //badal el mod estakhdemna bitwise and ma3 0x7fffffff 3ashan ne5od el lower 31 bits fa byeb2a nafs el natiga bs asra3
    //w 2^31 dh akbar rakam momken n storo f unsigned int 32-bit abl el overflow
    rand_seed = (1103515245 * rand_seed + 12345) & 0x7fffffff;
    return rand_seed;
}
#define SHUTDOWN_ADDR 0x100000
#define SHUTDOWN_SIZE 0x1000

uint64
sys_shutdown(void)
{
  (*(volatile uint32 *) 0x100000) = 0x5555;

  panic("sys_shutdown: shutdown failed");
  return 0;
}
