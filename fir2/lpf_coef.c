#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv){

  FILE *f1;

  if(argc != 2){
    printf("Usage : ./a output.raw\n");
    exit(-1);
  }

  if((f1 = fopen(argv[1], "wb")) == NULL){
    printf("Cannot open %s\n", argv[1]);
    exit(-2);
  }

  int tap = 1024;
  int fs = 48000;
  double fc = 1000.0;
  double sinc;
  double b[tap];

  for(int i = 0; i < tap; i++){
    int ii = i - (tap / 2);
    double w = 2.0 * M_PI * fc / fs;
    double x = w * ii;
    double sinc = 1.0;
    if(ii != 0){
      sinc = sin(x) / x;
    }
    b[i] = sinc;
  }

  double sum = 0.0;
  for(int i = 0; i < tap; i++){
    sum += b[i];
  }
  double invsum = 1.0 / sum;
  for(int i = 0; i < tap; i++){
    b[i] *= invsum;
  }
  
  for(int i = 0; i < tap; i++){
    fwrite(&b[i], sizeof(double), 1, f1);
  }
  
  fclose(f1);
  
  return 0;
}
