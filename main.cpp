#include <stdio.h>
#include <stdlib.h>
#include "functions.cpp"


int main (int argc, char** argv) {
  Grammar G;
  char y,*x ,* p = (char *) malloc(sizeof(char)*10);
  x=p;
  *x++='p';
  *x='\0';

  G['C']=p;


  printf("input: %s\n",argv[1]);
  printf("input: %s\n",argv[2]);

  next_gen(argv[1],argv[2],G);

  free(p);
  return 0;
}
