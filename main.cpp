#include <stdio.h>
#include <stdlib.h>
#include "functions.cpp"


int main (int argc, char** argv) {
  Grammar G;
  char y,*x ,* p = (char *) malloc(sizeof(char)*10);

  next_gen(argv[1],argv[2],G);

  free(p);
  return 0;
}
