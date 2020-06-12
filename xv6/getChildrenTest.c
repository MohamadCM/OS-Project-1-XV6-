#include "types.h"
#include "user.h"
#include "stat.h"

int main(void){


  int i = 0;
  int max = 3;
  int lock = 1;
  for(i = 0; i < max; i++) // loop will run n times (n = max)
  {
    if(fork() == 0)
    {
      if(lock == 1){ lock = 0;
        int ppid = getppid();
        int pid = getpid();
        int children = getChildren(ppid);
        printf(0,"Child [%d]: {PID: [%d], PPID: [%d], Parent's child ID's: <%d>}\n", i + 1, pid,ppid, children);
        lock = 1;
        exit();}
      } else wait();
    }
    for(i = 0; i < max; i++) // loop will run n times (n = max)
    wait();
    wait();
    exit();
  }
