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
#include "datetime.h"

// will work without this but to remove the error
#ifndef BOOT_EPOCH
#define BOOT_EPOCH
#endif

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

uint64
sys_shutdown(void)
{
  //0x10000 This is a physical memory addres eli aamalnalo define f vm.c momken yebaa ay haga tanya free(port)
  //this address triggers a shutdown of the emulated machine
  //el unit32* dh alashan el port da 32-bit fa lazm n3mel cast lel address deh 3ashan nektb feh
  //volatile alashan ne2ol lel compiler en el value deh momken yetghayar barra 3an taree2 el program fa may3melsh optimization 3aleha wa
  //ela msh hatetnafez alashan ehna shaghaleen memory-mapped I/O msh ram
  //el * eli bara deh 3ashan nektb fe el address deh
  //lama benhot 5555 eli m3arafenha f vm.c fel address dh blzat kaeno bytlob meno yshutdown
  (*(volatile uint32 *) 0x100000) = 0x5555;
  //panic btkhaly el system yhalt safely mn gher ma yfdal y1ol panic:kerneltrap w yetba3 el message deh law fe error
  panic("sys_shutdown: shutdown failed");
  //law shelna el retrun byhsal error lazem tkon mawgoda hata law msh hanewsallaha
  return 0;
}

uint64
sys_datetime(void)
{

  return 0;
}
