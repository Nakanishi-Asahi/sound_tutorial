#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fftw3.h>

#define TAP 8192

int main(int argc, char **argv){

  FILE *f1, *f2;

  if(argc != 3){
    printf("Usage : ./a input.raw output.raw\n");
    exit(-1);
  }

  if((f1 = fopen(argv[1], "rb")) == NULL){
    printf("Cannot open %s\n", argv[1]);
    exit(-2);
  }

  if((f2 = fopen(argv[2], "wb")) == NULL){
    printf("Cannot open %s\n", argv[2]);
    exit(-3);
  }

  int fs = 48000;
  double fc = 1000.0;
  int len = 48000;

  double invTAP = 1.0 / (double)TAP;

  //フィルタ係数の用意
  double sinc;
  double b[TAP];

  for(int i = 0; i < TAP; i++){
    int ii = i - (TAP / 2);
    double w = 2.0 * M_PI * fc / fs;
    double x = w * ii;
    double sinc = 1.0;
    if(ii != 0){
      sinc = sin(x) / x;
    }
    b[i] = sinc;
  }

  
  double sum = 0.0;
  for(int i = 0; i < TAP; i++){
    sum += b[i];
  }
  double invsum = 1.0 / sum;
  for(int i = 0; i < TAP; i++){
    b[i] *= invsum;
  }
  
  fftw_complex in_b[2 * TAP];
  fftw_complex out_b[2 * TAP];

  for(int i = 0; i < 2 * TAP; i++){
    in_b[i][0] = 0.0;
    in_b[i][1] = 0.0;
  }

  for(int i = 0; i < TAP; i++){
    in_b[i][0] = b[i];
    in_b[i][1] = 0.0;
  }

  fftw_plan fwd_b = fftw_plan_dft_1d(2 * TAP, in_b, out_b, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(fwd_b);

  fftw_complex in_i[2 * TAP];
  fftw_complex out_i[2 * TAP];

  //in_iの初期化
  for(int i = 0; i < 2 * TAP; i++){
    in_i[i][0] = 0.0;
    in_i[i][1] = 0.0;
  }

  double s;
  int in_count = 0;
  for(int i = 0; i < len; i++){
    //入力データ読み込み
    fread(&s, sizeof(double), 1, f1);
    in_i[in_count][0] = s;
    in_i[in_count][1] = 0.0;
    in_count++;
    //FFTとFIRフィルタを実行するのに十分な量の入力データが溜まったら…
    if(in_count >= TAP){
      //FFT実行
      fftw_plan fwd_i = fftw_plan_dft_1d(2 * TAP, in_i, out_i, FFTW_FORWARD, FFTW_ESTIMATE);
      fftw_execute(fwd_i);

      //周波数領域でのFIRフィルタの処理
      fftw_complex in[2 * TAP];
      fftw_complex out[2 * TAP];

      for(int j = 0; j < 2 * TAP; j++){
        double re = out_b[j][0] * out_i[j][0] - out_b[j][1] * out_i[j][1];
        double im = out_b[j][0] * out_i[j][1] + out_b[j][1] * out_i[j][0];
        in[j][0] = re;
        in[j][1] = im;
      }

      //IFFTの実行
      fftw_plan bwd = fftw_plan_dft_1d(2 * TAP, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);
      fftw_execute(bwd);

      //rawファイルに書き込み
      for(int j = 0; j < 2 * TAP; j++){
        double output = out[j][0] * (invTAP / 2);
        fwrite(&output, sizeof(double), 1, f2);
      }
      in_count = 0;
    }
  }
  return 0;
}
