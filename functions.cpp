#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stack>
// MAP Declaration
typedef std::map<char, std::string> Grammar;

// FUNCTIONS ----------------------------
// Declarations
int how_many(FILE* fp);
void read_grammar(char * infile, Grammar &G);
void next_gen(char* infile, char* outfile, Grammar &G);
void end_gen(char* infile, char* outfile);
std::string select_rule(std::string line);

// Prototypes
int how_many(FILE* fp) {
  fseek(fp, 0L, SEEK_END);
  int sz = ftell(fp);
  rewind(fp);
  return sz;
}

void read_grammar(char * infile, Grammar &G) {
  FILE* ifp = fopen(infile,"r");
  char c, *temp = (char*) malloc(sizeof(char)*50);
  std::string prod;
  int a,l,w, done=0;
  fscanf(ifp,"a:%d\n",&a);
  fscanf(ifp,"l:%d\n",&l);
  fscanf(ifp,"w:%d\n",&w);
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

void next_gen(char* infile, char*outfile, Grammar &G) {
  FILE* ifp = fopen(infile, "r");
  FILE* ofp = fopen(outfile, "w");
  int i, alt=0,len = how_many(ifp);
  char c;
  for (i=0;i<len;i++) {
    fscanf(ifp,"%c", &c);
    if (c < 91 && c > 64) {
      // capital letter
      if (c=='X') {fprintf(ofp, "%c", G[c][alt]); alt=1-alt;}
      else {fprintf(ofp, "%s", G[c].c_str());}
    }  else {
      // other aka bad input
      fprintf(ofp, "%c", c);
    }
  }
  fclose(ifp);
  fclose(ofp);
}

void end_gen(char* infile, char* outfile,Grammar &G) {
  FILE* ifp = fopen(infile, "r");
  FILE* ofp = fopen(outfile, "w");
  int i, len = how_many(ifp);
  char c;
  for (i=0;i<len;i++) {
    fscanf(ifp,"%c", &c);
    if (c < 91 && c > 64) {
      // capital letter
      if (G[c].length() == 1){
        fprintf(ofp, "%s", G[c].c_str());
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
    if (line.find('|')+1) {
      std::string* strs = new string [5];
      int i,j=0;
      for (i=0;i<line.length();i++) {
        if (line[i]!='|') {
          strs[j]+=line[i];
        } else {
          j++;
        }
      }
      return *strs[rand() % j];
    } else {
      return line;
    }
}
