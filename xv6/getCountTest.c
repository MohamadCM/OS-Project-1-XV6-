#include "types.h"
#include "user.h"
#include "stat.h"

int main(int argc,char *argv[]) {
  wait();
  wait();
  int input = atoi(argv[1]);
  int count = getCount(input);
  printf(0,"%d\n", count);
  exit();
}
