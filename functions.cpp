#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string>

// MAP Declaration
typedef std::map<char, std::string> Grammar;

// FUNCTIONS ----------------------------
// Declarations
int how_many(FILE* fp);
void read_grammar(char * infile, Grammar &G);
void next_gen(char* infile, char* outfile, Grammar &G);
void end_gen(char* infile, char* outfile);

// Prototypes
int how_many(FILE* fp) {
  fseek(fp, 0L, SEEK_END);
  int sz = ftell(fp);
  rewind(fp);
  return sz;
}

void read_grammar(char * infile, Grammar &G) {
  FILE* ifp = fopen(infile,"r");
  char c;
  std::string prod(20,'\0');
  int a,l,w, done=0;
  fscanf(ifp,"a:%d\n",&a);
  fscanf(ifp,"l:%d\n",&l);
  fscanf(ifp,"w:%d\n",&w);
  fscanf(ifp,"%c\n",&c);
  printf("%d",1);
  if (c=='{') {
    printf("%d",2);
    while (!done){
      printf("%d",3);
      fscanf(ifp,"%c",&c);
      if (c=='}') {
        printf("%d",5);
        done+=1;
      } else {
        printf("%d",4);
        fscanf(ifp,":%s\n", prod.data());
        G[c]=prod;
      }
    }
  }

  fclose(ifp);
}

void next_gen(char* infile, char*outfile, Grammar &G) {
  FILE* ifp = fopen(infile, "r");
  FILE* ofp = fopen(outfile, "w");
  int i, len = how_many(ifp);
  char c;
  for (i=0;i<len;i++) {
    fscanf(ifp,"%c", &c);
    if (c < 91 && c > 64) {
      // capital letter
      fprintf(ofp, "%s", G[c].c_str());
    } else if (c > 47 && c < 58) {
      // numerical character
      fprintf(ofp, "%c", c);
    } else if (c > 96 && c < 123) {
      // lower case letter
      fprintf(ofp, "%c", c);
    } else {
      // other aka bad input
      fprintf(ofp, "%c", c);
    }
  }
  fclose(ifp);
  fclose(ofp);
}

void end_gen(char* infile, char* outfile) {
  FILE* ifp = fopen(infile, "r");
  FILE* ofp = fopen(outfile, "w");
  int i, len = how_many(ifp);
  char c;
  for (i=0;i<len;i++) {
    fscanf(ifp,"%c", &c);
    if (c < 91 && c > 64) {
      // capital letter
      // fprintf(ofp, "%s", G[c]);
    } else if (c > 47 && c < 58) {
      // numerical character
      fprintf(ofp, "%c", c);
    } else if (c > 96 && c < 123) {
      // lower case letter
      fprintf(ofp, "%c", c);
    } else {
      // other aka bad input
      fprintf(ofp, "%c", c);
    }
  }
  fclose(ifp);
  fclose(ofp);
}
