#include <stdio.h>
#include <stdlib.h>
#include "functions.cpp"


int main (int argc, char** argv) {
  Grammar G;
  int c = 'A';
  printf("%d",c);
  char *x ,* p = (char *) malloc(sizeof(char)*5);
  x = p;
  *x++ = 'h';
  *x++ = 'e';
  *x++ = 'y';
  *x++ = '\0';
  G['C'] =  p;

  next_gen(".tmp1",".tmp2",G);
  free(p);

  return 0;
}
