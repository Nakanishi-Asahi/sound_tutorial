#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fftw3.h>

#define NUM 1024

int main(int argc, char **argv){
  
  FILE *f1, *f2, *f3, *f4;
  
  if(argc != 5){
    printf("Usage : ./a input.raw wave.txt fft.txt fft.raw\n");
    exit(-1);
  }
  
  if((f1 = fopen(argv[1], "rb")) == NULL){
    printf("Cannot open %s\n",argv[1]);
    exit(-2);
  }
  
  if((f2 = fopen(argv[2], "a")) == NULL){
    printf("Cannot open %s\n", argv[2]);
    exit(-3);
  }
  
  if((f3 = fopen(argv[3], "a")) == NULL){
    printf("Cannot open %s\n", argv[3]);
    exit(-4);
  }

  if((f4 = fopen(argv[4], "wb")) == NULL){
    printf("Cannot open %s\n", argv[4]);
    exit(-5);
  }
  
  int fs = 48000;
  int n;
  double s;
  fftw_complex in[2 * NUM];
  fftw_complex out[2 * NUM];
  
  for(n = 0; n < 2 * NUM; n++){
    in[n][0] = 0.0;
    in[n][1] = 0.0;
  }

  for(n = 0; n < NUM; n++){
    fread(&s, sizeof(double), 1, f1);
    printf("%d : %f\n", n, s);
    fprintf(f2, "%d %f\n", n, s);
    
    double re = s;
    double im = 0.0;
    
    in[n][0] = re;
    in[n][1] = im;
  }

  fftw_plan fwd = fftw_plan_dft_1d(2 * NUM, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

  fftw_execute(fwd);

  for(int i = 0; i < 2 * NUM; i++){
    double re = out[i][0];
    double im = out[i][1];
    double amp = sqrt(re * re + im * im);
    double freq = (double)fs * (double)i / (double)(2 * NUM);
    double dB = 20.0 * log10(fabs(amp));
    fprintf(f3, "%f %f\n", freq, dB);
    fwrite(&out[i], sizeof(fftw_complex), 1, f4);
  }

  fclose(f1);
  fclose(f2);
  fclose(f3);
  fclose(f4);

  fftw_destroy_plan(fwd);

  return EXIT_SUCCESS;
}
