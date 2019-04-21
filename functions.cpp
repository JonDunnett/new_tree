#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stack>
#include <math.h>
#include <vector>

#ifndef _FUNCTIONS
#define _FUNCTIONS
// MAP Declaration
typedef std::map<char, std::string> Grammar;
// PI Definition
#define PI 3.14159265

// FUNCTIONS ----------------------------
// Declarations
int how_many(FILE* fp);
void read_grammar(char * infile, Grammar &G);
void next_gen(char* infile, Grammar &G);
void end_gen(char* infile, char* outfile);
std::string select_rule(std::string line);
float mcos(float angle);
float msin(float anngle);
void  translate(Rectangle rect, const std::vector<Matrix> matrices);
void cp(char * in, char * out);
int chartoint(char c);
int multicti(char * c);
int exp(int x, int pow); 
// Prototypes
int how_many(FILE* fp) {
// Counts the number of characters in the given file
// PRE : An initialized file pointer in read mode; must point to beginning of an
//       existing file
// POST: Returns integer number of characters in the file; fp returned to
//       beginning of file
  fseek(fp, 0L, SEEK_END);
  int sz = ftell(fp);
  rewind(fp);
  return sz;
}

void read_grammar(char * infile, Grammar &G) {
// Parses grammar file and adds rules to Grammar map
// PRE : Instantiated empty grammar map; file containing grammar definition
// POST: File opened and closed; grammar map initialized with rules
  FILE* ifp = fopen(infile,"r");
  char c, *temp = (char*) malloc(sizeof(char)*50);
  std::string prod;
  int done=0;
  fscanf(ifp,"%c\n",&c);
  if (c=='{') {
    while (!done){
      prod="";
      fscanf(ifp,"%c",&c);
      if (c=='}') {
        done+=1;
      } else {
        fscanf(ifp,":%s\n", temp);
        prod = std::string(temp);
        G[c]=prod;
      }
    }
  }

  fclose(ifp);
}

void next_gen(char* infile, Grammar &G) {
// iterate generation as specified by grammar
// PRE : existing infile; initialized Grammar
// POST: infile parsed; rules defined by grammar iterated one generation and
//       output to outfile
  FILE* ifp = fopen(infile, "r");
  FILE* ofp = fopen(".tmp", "w");
  int i, alt=0,len = how_many(ifp);
  char c;
  for (i=0;i<len;i++) {
    fscanf(ifp,"%c", &c);
    if (c < 91 && c > 64) {
      // capital letter
      if (c=='D') {fprintf(ofp, "%c", G[c][alt]); alt=1-alt;}
      else {fprintf(ofp, "%s", select_rule(G[c]).c_str());}
    }  else {
      // other aka bad input
      fprintf(ofp, "%c", c);
    }
  }
  fclose(ifp);
  fclose(ofp);
  cp(".tmp",infile);
}

void end_gen(char* infile, char* outfile,Grammar &G) {
// clear non-terminals for final output
// PRE : existing infile; initialized Grammar
// POST: infile parsed; non-terminals with single character terminal production
//       iterated one generation; other non-terminals removed; output to outfile
  FILE* ifp = fopen(infile, "r");
  FILE* ofp = fopen(outfile, "w");
  int i, len = how_many(ifp);
  char c;
  for (i=0;i<len;i++) {
    fscanf(ifp,"%c", &c);
    if (c < 91 && c > 64) {
      // capital letter
      if (select_rule(G[c]).length() == 1){
        fprintf(ofp, "%s", select_rule(G[c]).c_str());
      }
    } else {
      // other
      fprintf(ofp, "%c", c);
    }
  }
  fprintf(ofp,"%c",';');
  fclose(ifp);
  fclose(ofp);
}

std::string select_rule(std::string line) {
// selects a single production from string with multiple possibilities delimited
// by the '|' character
// PRE : existing string holding all possible productions (may only be one)
// POST: returns a string holding a random single production
    if (line.find('|')+1) {
      std::string* strs = new std::string [10];
      int i=0,j=0;
      for (i=0;i<line.length();i++) {
        if (line[i]!='|') {
          strs[j]+=line[i];
        } else {
          j++;
        }
      }
      return strs[rand() % ++j];
    } else {
      return line;
    }
}


float msin(float angle) {
// my sine function takes an angle not radians
// PRE : valid float angle
// POST: returns sine of given angle
  return sin(angle*PI/180);
}
float mcos(float angle){
// my cosine function takes an angle not radians
// PRE : valid float angle
// POST: returns cosine of given angle
  return cos(angle*PI/180);
}


void translate(Rectangle rect, const std::vector<Matrix> matrices) {
// translate rectangle using the series of matrices stored in vector 
// PRE : Rectangle rect must be initialized with points corresponding to
//       the desired starting point.  
// POST: Rectangle rect will be translated, this modifies the object! 
  Matrix* M; 
  for (short i=0;i<matrices.size();i++) {
    rect.transform(matrices[i]);        
  }

}

void cp(char * in, char * out) {
// copy file contents from in to out
// PRE : infile and outfile not opened
// POST: contents from in transfered to out
  FILE * infile  = fopen(in,"r"),
       * outfile = fopen(out,"w");

  int limit = how_many(infile);
  char t;
  for (short i=0;i<limit;i++) {
    fscanf(infile, "%c", &t);
    fprintf(outfile, "%c", t);
  }   
  fclose(infile);
  fclose(outfile);   
}

int chartoint(char c) {
// convert char to int
// PRE : Must be a char representing an integer
// POST: returned integer value
  return -1*('0'-c);
}

int multicti(char * c) {
// convert string to integer
// PRE : Existing null terminated string c
// POST: returned integer value
  int j=0,i=0,sum=0;
  char * p=c;
  while(*p!='\0'){i++;p++;}
  while (i>j){
    sum+= chartoint(*(--p))*exp(10,j++); 
  }
  
  return sum;
}

int exp(int x, int pow) {
// exponentiate integer
// PRE : existing integers
// POST: returns x^pow
  int ans=1;
  for(;pow>0;--pow) {
    ans = ans * x;
  }
  return ans;
}
#endif 
