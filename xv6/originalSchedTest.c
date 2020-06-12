#include "types.h"
#include "user.h"
#include "stat.h"

int main(void){
  int averageTT = 0;
  int averageWT = 0;
  int averageCBT = 0;
  changePolicy(1); // Set policy to Modified_Sheduling_algorithm
  int i = 0;
  int tmp = 0;
  for(i = 0; i < 10; i++){
    if((tmp = fork()) == 0){
      int j;
      for(j = 0; j < 1000; j++){
        printf(0,"|%d|: |%d|\n", getpid(), j);
      }
    } else if(tmp > 0){
      struct timeVariables* t = malloc(sizeof(struct timeVariables));
      waitForChild(t);
      int turnaround = t->creationTime - t->terminationTime;
      int waiting = turnaround - t->runningTime;
      printf(0,"CBT: %d; Turnaround Time: %d; Waiting Time: %d\n", t->runningTime, turnaround, waiting);
      averageCBT += t->runningTime;
      averageTT += turnaround;
      averageWT += waiting;
    } if(tmp == -1){
      printf(0,"%s\n", "Fork failed, exiting");
      exit();
    }
  }
  if(tmp > 0){
    averageCBT /= 10;
    averageTT /= 10;
    averageWT /= 10;
    printf(0,"\n=>Average CBT = %d; Average Turnaround Time = %d; Average Waiting Time = %d<=\n", averageCBT, averageTT, averageWT);
  }
  exit();
}
