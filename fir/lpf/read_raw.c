#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv){

  if(argc != 3){
    printf("Usage : ./a input.raw wave.txt\n");
    exit(-1);
  }

  FILE *f1, *f2;

  if((f1 = fopen(argv[1], "rb")) == NULL){
    printf("Cannot open %s\n", argv[1]);
    exit(-2);
  }

  if((f2 = fopen(argv[2], "w")) == NULL){
    printf("Cannot open %s\n", argv[2]);
    exit(-3);
  }

  int len = 48000;

  double s;

  for(int i = 0; i < len; i++){
    fread(&s, sizeof(double), 1, f1);
    fprintf(f2, "%d %f\n", i, s);
  }

  fclose(f1);
  fclose(f2);

  return 0;
}
