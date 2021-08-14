#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv){

  FILE *f1;

  if(argc != 2){
    printf("Usage : ./a output.raw\n");
    exit(-1);
  }

  if((f1 = fopen(argv[1], "wb")) == NULL){
    printf("Cannot open %s\n", argv[1]);
    exit(-2);
  }

  int len = 1024;
  double s;

  for(int i = 0; i < len; i++){
    if(i == 0){
      s = 1.0;
    }
    else{
      s = 0.0;
    }
    fwrite(&s, sizeof(double), 1, f1);
  }

  fclose(f1);

  return 0;
}
