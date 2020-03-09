// main.cpp
// --- HEADER ------------------------------------------------------------------
// SUMMARY :
// CREATOR :
// EDITS   :
// STATUS  : 
// -----------------------------------------------------------------------------

// --- INCLUDES ----------------------------------------------------------------
#include <stdio.h> 
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "classes.cpp"
#include "functions.cpp"
// -----------------------------------------------------------------------------

// --- CONSTANTS ---------------------------------------------------------------
// -----------------------------------------------------------------------------

// --- MAIN -------------------------------------------------------------------- 
int main (int argc, char** argv) {
  srand(0);
  Grammar G;
  
  read_grammar(argv[2],G);
  FILE * fp = fopen(".at","w");
  fprintf(fp,"%s",(select_rule(G['S'])).c_str());
  fclose(fp);
  int limit=multicti(argv[1]);
  for(short i=0;i<limit;i++) {
    next_gen(".at",G);
  } // swi is final output
  //const char finalfname = "final.txt";
  end_gen(".at","final.txt"/*finalfname*/, G);

  char c,s;
  std::vector<Matrix> matrices; // vector acting as a stack so we can still 
                                // iterate though  
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

  
  Rectangle rect; 
  Triangle tri;    
 
  // output rectangle on origin
  tri = rect.upper(); // Segfault
  tri.output("tree.stl");
  tri = rect.lower(); // Segfault
  tri.output("tree.stl");


// parsing output tree
  do {
    fscanf(fp,"%c",&c);
    if (c=='[') {
      // new branch
      fscanf(fp,"%c",&s); // get +/-
      if (s == '+') {
        matrices.push_back(Matrix(&PLUS));
      } else if (s=='-') {
        matrices.push_back(Matrix(&MINU));
      }
      // for now we're just gonna leave it as [+[-[+]]]
      // maybe we'll be more flexible later
      // STEPS:
      // 1) create rectangle on origin
        rect = Rectangle();  // default ctor place rectangle on origin
      // 2) translate rectangle
        translate(rect,matrices); 	
      // 3) convert to triangle and output
        //tri = rect.upper();
      	tri.output("tree.stl");
        //tri = rect.lower();
        tri.output("tree.stl");
    } else if (c==']') {
      // pop branch
      matrices.pop_back();
    }
  } while (c!=';');

  printf("%s\n","");
  return 0;
}
