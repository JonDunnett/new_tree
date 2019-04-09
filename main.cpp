#include <stdio.h>
#include <stdlib.h>
#include "functions.cpp"


int main (int argc, char** argv) {
  srand(0/*(unsigned int*) malloc(sizeof(unsigned int))*/);
  Grammar G;

  read_grammar(argv[3],G);
  FILE * fp = fopen(argv[1],"w");
  fprintf(fp,"%s",(select_rule(G['S'])).c_str());
  fclose(fp);

  int swi=0,tch=1;
  for(short i=0;i<20;i++) {
    next_gen(argv[swi+1],argv[tch+1],G);
    swi=1-swi;tch=1-tch;
  } // swi is final output
  //const char finalfname = "final.txt";
  end_gen(argv[swi+1],"final.txt"/*finalfname*/, G);

  char c,s;
  std::stack<char> matrices; // need to init stack with [ Identity matrix ]
  fp = fopen("final.txt", "r");

  //Matrix PLUS = 0; // translation for a branch off to the right
  //Matrix MINU = 0; // translation for a branch off to the left

  /* TRANSLATION MATRIX FORM
  [
    [cos(theta),-sin(theta), dx ],
    [sin(theta), cos(theta), dy ],
    [     0    ,     0     ,  1 ]
  ]
  */

  do {
    fscanf(fp,"%c",&c);
    if (c=='[') {
      // new branch
      fscanf(fp,"%c",&s); // get +/-
      if (s == '+' || s=='-') {
        matrices.push(s);
      }
      // for now we're just gonna leave it as [+[-[+]]]
      // maybe we'll be more flexible later
      // STEPS:
      // 1) create rectangle on origin
      // 2) translate rectangle
      // 3) convert to triangle
      // 4) calculate normal
      // 5) output triangle
      // 6) add +/- matrix to stack  => matrices.push_back(Matrix(PLUS))
      //    add a copy of plus or minus to the stack
    } else if (c==']') {
      // pop branch
      printf("%c",matrices.top());
      matrices.pop();
    }
  } while (c!=';');
  printf("%s\n","");

  return 0;
}
