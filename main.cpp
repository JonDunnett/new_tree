#include <stdio.h>
#include <stdlib.h>
#include "functions.cpp"


int main (int argc, char** argv) {
  Grammar G;
  char y,*x ,* p = (char *) malloc(sizeof(char)*10);
  x=p;
  *x++='p';
  *x++='C';
  *x='\0';

  G['C']=p;
  int swi=0,tch=1;
  for(short i=0;i<1000;i++) {
    next_gen(argv[swi+1],argv[tch+1],G);
    swi=1-swi;tch=1-tch;
  } // swi is final output
  free(p);
  return 0;
}
