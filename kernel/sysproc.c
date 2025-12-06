#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "perfmetrics.h"

// Scheduler mode constants
#define SCHED_ROUND_ROBIN 0
#define SCHED_FCFS        1
#define SCHED_PRIORITY_BASED    2

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
// uint64
// sys_uptime(void)
// {
//   uint xticks;

//   acquire(&tickslock);
//   xticks = ticks;
//   release(&tickslock);
//   return xticks;
// }
uint64
sys_getppid(void)
{
  struct proc *p = myproc();
  return p->parent->pid;
}

extern int total_syscalls;
uint64
sys_countsyscall(void)
{
  return total_syscalls;
}
extern uint ticks;

uint64
sys_uptime(void)
{
  return ticks;
}

// get process table system call
uint64
sys_getptable(void)
{
  int nproc;
  uint64 buf;

  // get first argument (number of processes)
  argint(0, &nproc);

  // get second argument (pointer to buffer)
  argaddr(1, &buf);

  return getptable(nproc, buf);
}

uint64
sys_setsched(void)
{
  int mode;
  extern int sched_mode;

  argint(0, &mode);

  // Validate scheduler mode
  if(mode < SCHED_ROUND_ROBIN || mode > SCHED_PRIORITY_BASED) {
    return -1;  // Invalid mode
  }

  sched_mode = mode;
  return 0;  // Success
}

uint64
sys_perfmetrics(void)
{
  uint64 addr;
  struct perfmetrics pm;

  argaddr(0, &addr);  // Get user buffer address

  perfmetrics(&pm);  // Calculate the metrics

  // Copy to user space
  if(copyout(myproc()->pagetable, addr, (char*)&pm, sizeof(pm)) < 0)
      return -1;

  return 0;  // Success
}
