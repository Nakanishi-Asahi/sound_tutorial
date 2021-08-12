#include <stdio.h>
#include <stdlib.h>
#include <fftw3.h>

#define NUM 1024

int main(int argc, char **argv){

  FILE *f1, *f2, *f3;
  
  if(argc != 4){
    printf("Usage : ./a input1.raw input2.raw fft.txt ifft.txt\n");
    exit(-1);
  }

  if((f1 = fopen(argv[1], "rb")) == NULL){
    printf("Cannot open %s\n", argv[1]);
    exit(-2);
  }

  if((f2 = fopen(argv[2], "rb")) == NULL){
    printf("Cannot open %s\n", argv[2]);
    exit(-3);
  }

  if((f3 = fopen(argv[3], "a")) == NULL){
    printf("Cannot open %s\n", argv[3]);
    exit(-4);
  }

  if((f4 = fopen(argv[4], "a")) == NULL){
    printf("Cannot open %s\n", argv[4]);
    exit(-5);
  }

  int fs = 48000;

  fftw_complex v1, v2;
  double re, im;
  fftw_complex in[2 * NUM], out[2 * NUM];
  
  for(int i = 0; i < 2 * NUM; i++){
    fread(&v1, sizeof(fftw_complex), 1, f1);
    fread(&v2, sizeof(fftw_complex), 1, f2);
    re = v1[0] * v2[0] - v1[1] * v2[1];
    im = v1[0] * v2[1] + v1[1] * v2[0];
    in[i][0] = re;
    in[i][1] = im;
    double amp = sqrt(re * re + im * im);
  }

  fftw_plan bwd = fftw_plan_dft_1d(2 * NUM, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);
  fftw_execute(bwd);

  for(int i = 0; i < 2 * NUM; i++){
    double re = out[i][0];
    double im = out[i][1];
    fprintf(f4, "%d %f\n", i, re);
  }

  fclose(f1);
  fclose(f2);
  fclose(f3);

  fftw_destroy_plan(bwd);

  return EXIT_SUCCESS;
}
