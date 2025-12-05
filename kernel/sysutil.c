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
#define BOOT_EPOCH 0
#endif

// Time conversion constants
#define TICKS_PER_SECOND 10000000   // 10 MHz timer
#define SECONDS_PER_MINUTE 60
#define SECONDS_PER_HOUR 3600
#define SECONDS_PER_DAY 86400
#define DAYS_PER_YEAR 365
#define UNIX_EPOCH_YEAR 1970
#define TIMEZONE_OFFSET 7200  // Offset in seconds (+2 hours for egypt time = 7200)

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

// function to check if a year is a leap year
static int
is_leap_year(int year)
{
  // A year is a leap year if:
  // - Divisible by 4 AND
  // - (NOT divisible by 100 OR divisible by 400)
  return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}

uint64
sys_datetime(void)
{
  uint64 useraddr;
  struct datetime dt;

  // Get the user-space pointer to struct datetime
  argaddr(0, &useraddr);

  // Read the hardware timer and convert to Unix timestamp
  uint64 elapsed_ticks = r_time();  // Get hardware timer ticks
  uint64 elapsed_seconds = elapsed_ticks / TICKS_PER_SECOND;  // Convert to seconds
  uint64 unix_timestamp = BOOT_EPOCH + elapsed_seconds + TIMEZONE_OFFSET;  // Add boot epoch and timezone offset

  // Convert Unix timestamp to datetime components
  uint64 remaining_seconds = unix_timestamp;

  // Calculate years since 1970
  int year = UNIX_EPOCH_YEAR;
  while(1) {
    int days_this_year = is_leap_year(year) ? 366 : 365;
    uint64 seconds_this_year = days_this_year * SECONDS_PER_DAY;

    if(remaining_seconds < seconds_this_year)
      break;

    remaining_seconds -= seconds_this_year;
    year++;
  }
  dt.year = year;

  // Calculate month and day
  int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if(is_leap_year(year))
    days_in_month[1] = 29;  // February has 29 days in leap year

  int remaining_days = remaining_seconds / SECONDS_PER_DAY;
  remaining_seconds %= SECONDS_PER_DAY;

  int month = 0;
  while(month < 12 && remaining_days >= days_in_month[month]) {
    remaining_days -= days_in_month[month];
    month++;
  }
  dt.month = month + 1;  // Months are 1-12
  dt.day = remaining_days + 1;  // Days are 1-31

  // Calculate time components
  dt.hour = remaining_seconds / SECONDS_PER_HOUR;
  remaining_seconds %= SECONDS_PER_HOUR;
  dt.minute = remaining_seconds / SECONDS_PER_MINUTE;
  dt.second = remaining_seconds % SECONDS_PER_MINUTE;

  // Copy the datetime struct to user space
  if(copyout(myproc()->pagetable, useraddr, (char *)&dt, sizeof(dt)) < 0)
    return -1;

  return 0;
}
