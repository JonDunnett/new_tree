#include <stdio.h>
#include <stdlib.h>

int how_many(FILE* fp);
char* read(char * filename);
int write(char * filename, char * data) ;

int how_many(FILE* fp) {
  fseek(fp, 0L, SEEK_END);
  int sz = ftell(fp);
  rewind(fp);
  return sz;
}

char* read(char * filename) {
  FILE* fp = fopen(filename, "r");
  int len = how_many(fp);
  char* ins,* data = (char*) malloc(sizeof(char)*len);
  int i;
  ins = data;
  for(i=0;i<len-1;i++){
    fscanf(fp,"%c", ins);
    ins++;
  }
  *ins='\0';
  fclose(fp);
  return data;
}

int write(char * filename, char * data) {
  FILE *fp = fopen(filename,"w");
  fprintf(fp, "%s", data);
  free(data);
  fclose(fp);
  return 1;
}

int main (int argc, char** argv) {
  char* data = read(argv[1]);
  *data = 'p';
  write(argv[1],data);
  return 0;
}
