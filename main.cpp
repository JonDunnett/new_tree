#include <stdio.h>
#include <stdlib.h>
#include "functions.cpp"


int main (int argc, char** argv) {
  Grammar G;
  char y,*x ,* p = (char *) malloc(sizeof(char)*10);

  printf("%s","iterate generation? [y=yes]");
  y=getchar();
  int swi=0,tch=1;
  while (y!='y') {
    next_gen(argv[swi+1],argv[tch+1],G);
    swi = 1-swi;
    tch = 1-tch;
  }

  free(p);
  return 0;
}
