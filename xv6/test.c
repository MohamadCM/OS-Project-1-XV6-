#include "types.h"
#include "user.h"
#include "stat.h"

int main(void){
  struct timeVariables* t = malloc(sizeof(struct timeVariables));
  changePolicy(2);

  int tmp = fork();
  //printf(0,"%d\n", );
  if(tmp == 0){
    printf(0,"%s\n", "Waitng");
  } else{
    waitForChild(t);
    printf(0, "%d\n", t->runningTime);
    printf(0, "%d\n", t->readyTime);
  }
  exit();
}
