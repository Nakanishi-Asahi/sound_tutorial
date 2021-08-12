#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAP 2048

double sinc(double x){
  if(x == 0.0){
    return 1;
  }
  else{
    return sin(x) / x;
  }
}



int main(int argc, char **argv){
  if(argc != 3){
    printf("Usage : ./a input.raw output.raw\n");
    exit(-1);
  }
  
  FILE *f1, *f2;
  
  if((f1 = fopen(argv[1], "rb")) == NULL){
    printf("Cannot open %s\n", argv[1]);
    exit(-2);
  }
  
  if((f2 = fopen(argv[2], "a")) == NULL){
    printf("Cannot open %s\n", argv[2]);
    exit(-3);
  }
  
  int len = 48000;
  
  int fs = 48000;
  double f0 = 1000.0;
  
  double fe = f0 / (double)fs;
  
  double coef[TAP];

  for(int m = 0; m < TAP; m++){
    if(m == TAP / 2){
      coef[m] = 2.0 * fe;
    }
    else{
      coef[m] = 2.0 * fe * sin(2.0 * M_PI * fe * (double)(m - TAP / 2)) / (2.0 * M_PI * fe * (double)(m - TAP / 2));
    }
    fprintf(f2, "%d %f\n", m, coef[m]);
  }
  /*
  double input;
  double x_tmp[TAP];
  int count = 0;

  double pre_y_tail[TAP];
  for(int i = 0; i < TAP; i++){
    pre_y_tail[i] = 0.0;
  }

  for(int n = 0; n < len; n++){
    fread(&input, sizeof(double), 1, f1);
    x_tmp[count] = input;
    count++;
    
    if(count >= TAP){

      double x_fir[3 * TAP - 2];
      for(int i = 0; i < 3 * TAP - 2; i++){
	if(i < TAP - 1 || 2 * TAP - 2 < i){
	  x_fir[i] = 0.0;
	}
	else{
	  x_fir[i] = x_tmp[i - (TAP - 1)];
	}
      }

      double y_tmp[2 * TAP];
      y_tmp[0] = 0.0;
      for(int i = 0; i < 2 * TAP - 1; i++){
	//printf("i : %d\n", i);
	y_tmp[i + 1] = 0.0;
	for(int j = 0; j < TAP; j++){
	  //printf("j : %d\n", j);
	  y_tmp[i + 1] += coef[j] * x_fir[i + j];
	}
      }

      double y_head[TAP];
      double y_tail[TAP];
      int head_count = 0;
      int tail_count = 0;

      for(int i = 0; i < 2 * TAP; i++){
	if(i < TAP){
	  y_head[head_count] = y_tmp[i];
	  head_count++;
	}
	else{
	  y_tail[tail_count] = y_tmp[i];
	  tail_count++;
	}
      }

      double y[TAP];
      for(int i = 0; i < TAP; i++){
	y[i] = y_head[i] + pre_y_tail[i];
	pre_y_tail[i] = y_tail[i];
      }

      for(int i = 0; i < TAP; i++){
	fwrite(&y[i], sizeof(double), 1, f2);
      }
      count = 0;
    }
  }
  */
  fclose(f1);
  fclose(f2);
  return 0;
}
