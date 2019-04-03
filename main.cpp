#include <stdio.h>
#include <stdlib.h>
#include "functions.cpp"


int main (int argc, char** argv) {
  Grammar G;

  read_grammar(argv[3],G);
  FILE * fp = fopen(argv[1],"w");
  fprintf(fp,"%s",G['S'].c_str());
  //printf("%s\n",G['S'].c_str());
  //printf("%s\n",G['B'].c_str());
  //printf("%s\n",G['A'].c_str());
  fclose(fp);

  int swi=0,tch=1;
  for(short i=0;i<15;i++) {
    next_gen(argv[swi+1],argv[tch+1],G);
    swi=1-swi;tch=1-tch;
  } // swi is final output

  end_gen(argv[swi+1],"final.txt", G);

  return 0;
}

/*
char y,*x ,* p = (char *) malloc(sizeof(char)*10);
x=p;
*x++='p';
*x++='C';
*x++='C';
*x++='p';
*x='\0';

G['C']=p;
*/
