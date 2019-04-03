

// MAP Declaration
typedef map<char, char*> Grammar;

// FUNCTIONS ----------------------------
// Declarations
int how_many(FILE* fp);
char* read(char * filename);
int write(char * filename, char * data);


// Prototypes
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


void next_gen(char* infile, char*outfile, Grammar &G) {
  FILE* ifp = fopen(infile, "r");
  FILE* ofp = fopen(outfile, "w");
  int i, c, len = how_many(ifp);
  for (i=0;i<len;i++) {
    fscanf(ifp,"%c", &c);
    if (c < 91 && c > 64) {
      // capital letter
      fprintf(ofp, "%s", )
    }
  }



  fclose(ifp);
  fclose(ofp);
}
