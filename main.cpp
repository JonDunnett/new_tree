#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "classes.cpp"
#include "functions.cpp"


// main function 
int main (int argc, char** argv) {
  srand(0);
  Grammar G;
  
  read_grammar(argv[2],G);
  FILE * fp = fopen(".at","w");
  fprintf(fp,"%s",(select_rule(G['S'])).c_str());
  fclose(fp);
  for(short i=0;i<multicti(argv[1]);i++) {
    next_gen(".at",G);
  } // swi is final output
  //const char finalfname = "final.txt";
  end_gen(".at","final.txt"/*finalfname*/, G);

  char c,s;
  std::vector<Matrix> matrices; // need to init stack with [ Identity matrix ]
  fp = fopen("final.txt", "r");

  Matrix PLUS(3,3); // translation for a branch off to the right
  Matrix MINU(3,3); // translation for a branch off to the left

  /* 

  TRANSLATION MATRIX FORM
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

  
  Rectangle rect; // double free or corruption
  //Triangle tri;   // Segfault
 
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
