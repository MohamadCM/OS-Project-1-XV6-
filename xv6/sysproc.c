#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"


int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// return process's parant PID
int
sys_getppid(void)
{
return myproc()->parent->pid;
}
// return PID of process's children
int
sys_getChildren(int pid)
{
  cli();
  argint(0, &pid);
  int i, result = 0;
  if(sys_getppid() == pid){
    for(i = 0; i < myproc()->parent->number_of_children; i++){
      int tmp = myproc()->number_of_children / 10;
      result *= 10;
      if(tmp > 0)
        result *= 10;
      result += myproc()->parent->children[i];}
}  else{
  for(i = 0; i < myproc()->number_of_children; i++){
    int tmp = myproc()->number_of_children / 10;
    result *= 10;
    if(tmp > 0)
      result *= 10;
    result += myproc()->children[i];}
  }
  sti();
  return result;
}
// return number of times that a specific systemcall was called
int
sys_getCount(int number){
  cli();
  argint(0, &number);
  if(number < 1 || number > 22){
    sti();
    return -1;}
    sti();
  return myproc()->sys_call_count[number];
}

// Change priority of a process
// Return 1 if succesfull, 0 otherwise
int
sys_changePriority(int priority){
  argint(0, &priority);
  if(priority < 1 || priority > 5)
    return -1;
  myproc()->priority = priority;
  return 1;
}

// Change scheduling policy
int
sys_changePolicy(int policy){
  argint(0, &policy);
  if(policy >= 3 || policy < 0)
    return -1;
  current_sheduling_algorithm = policy;
  return 1;
}

// Modified wait system call
int
sys_waitForChild(struct timeVariables* times){
  return waitForChild(times);
}
