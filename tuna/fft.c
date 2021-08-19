#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fftw3.h>

#define NUM 16384

int main(int argc, char **argv){
	
	double invNUM = 1.0 / NUM;

	FILE *f1, *f2, *f3;

	if(argc != 4){
		printf("Usage : ./a input.raw wave.txt fft.txt\n");
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

	int fs = 48000;
	int len = 48000;

	int n;
	double s;
	int count = 0;
	fftw_complex in[NUM];
	fftw_complex out[NUM];

	int fft_count = 0;

	for(n = 0; n < len; n++){
		fread(&s, sizeof(double), 1, f1);
		fprintf(f2, "%d %f\n", n, s);

		double re = s;
		double im = 0;

		in[count][0] = re;
		in[count][1] = im;
		count++;
		if(count >= NUM){
			fftw_plan fwd = fftw_plan_dft_1d(NUM, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
			fftw_execute(fwd);
			for(int i = 0; i < NUM; i++){
				double re = out[i][0];
				double im = out[i][1];
				/*
				if(i != 0||i != NUM/2){
					re *= invNUM * 2;
					im *= invNUM * 2;
				}
				*/
				double amp = sqrt(re * re + im * im);
				double rad;
				if(fabs(re) < 1e-6){
					if(im > 0){
						rad = M_PI / 2;
					}
					else{
						rad = -M_PI / 2;
					}
				}
				else{
					rad = atan2(im, re);
				}
				double deg = rad / M_PI * 180;
				double freq = (double)fs * (double)i / (double)NUM;
				double dB = 20.0 * log10(fabs(amp));
				if(fft_count == 0){
					fprintf(f3, "%.20f %.20f\n", freq, dB);
				}
			}

			fft_count++;

			fftw_destroy_plan(fwd);
			count = 0;
		}
	}
	
	fclose(f1);
	fclose(f2);
	fclose(f3);

	return EXIT_SUCCESS;
}

