#include <stdio.h>
#include <stdlib.h>
#include "classes.cpp"
#include "functions.cpp"
#include <math.h>
#include <vector>


// main function 
int main (int argc, char** argv) {
  srand(0);
  Grammar G;

  read_grammar(argv[3],G);
  FILE * fp = fopen(argv[1],"w");
  fprintf(fp,"%s",(select_rule(G['S'])).c_str());
  fclose(fp);
  
  int swi=0,tch=1;
  for(short i=0;i<10;i++) {
    next_gen(argv[swi+1],argv[tch+1],G);
    swi=1-swi;tch=1-tch;
  } // swi is final output
  //const char finalfname = "final.txt";
  end_gen(argv[swi+1],"final.txt"/*finalfname*/, G);

  char c,s;
  //std::vector<Matrix> matrices; // need to init stack with [ Identity matrix ]
  fp = fopen("final.txt", "r");

  Matrix PLUS(3,3); // translation for a branch off to the right
  Matrix MINU(3,3); // translation for a branch off to the left

  /* TRANSLATION MATRIX FORM
  [
    [cos(theta),-sin(theta), dx ],  
    [sin(theta), cos(theta), dy ],
    [     0    ,     0     ,  1 ]
  ]

  */



  PLUS.set_value(0,0,   mcos(10));
  PLUS.set_value(0,1,-1*msin(10));
  PLUS.set_value(1,0,   msin(10));
  PLUS.set_value(1,1,   mcos(10));

  MINU.set_value(0,0,   mcos(-10)); // this can also be 350 if needed #GEOMETRY
  MINU.set_value(0,1,-1*msin(-10));
  MINU.set_value(1,0,   msin(-10));
  MINU.set_value(1,1,   mcos(-10));

  
  //Rectangle rect;
  //Triangle tri;
 
 // output rectangle on origin
  //rect = Rectangle();
  //tri = Triangle(rect.upper());
  //tri.output();/* either std::fout || filename * /);

/*
// parsing output tree
  do {
    fscanf(fp,"%c",&c);
    if (c=='[') {
      // new branch
      fscanf(fp,"%c",&s); // get +/-
      if (s == '+') {
        matrices.push_back(Matrix(PLUS));
      } else if (s=='-') {
        matrices.push_back(Matrix(MINU));
      }
      // for now we're just gonna leave it as [+[-[+]]]
      // maybe we'll be more flexible later
      // STEPS:
      // 1) create rectangle on origin
        rect = Rectangle();
      // 2) translate rectangle
        translate(rect,matrices); 	
      // 3) convert to triangle and output
        tri = Triangle(rect.upper());
      	tri.output(/* either std::fout || filename * /);
        tri = Triangle(rect.lower());
        tri.output(/* either std::fout || filename * /);
      // 4) output triangle
      // 5) add +/- matrix to stack  => matrices.push_back(Matrix(PLUS))
      //    add a copy of plus or minus to the stack
    } else if (c==']') {
      // pop branch
      matrices.pop_back();
    }
  } while (c!=';');
*/
  printf("%s\n","");
  return 0;
}
