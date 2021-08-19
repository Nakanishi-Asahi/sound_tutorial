#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

	if((f2 = fopen(argv[2], "wb")) == NULL){
		printf("Cannot open %s\n", argv[2]);
		exit(-3);
	}
	
	int len = 48000;

	int fs = 48000;
	double f0 = 1000.0;
	double dBgain = -3.0;
	double Q = 1.0 / sqrt(2.0);

	double A = pow(10.0, (dBgain / 40.0));
	double omega = 2.0 * M_PI * f0 / (double)fs;
	double cos_omega = cos(omega);
	double sin_omega = sin(omega);
	double alpha = sin_omega / (2.0 * Q);

	double b[3] = {
		(1.0 + cos_omega) / 2.0,
		-(1.0 + cos_omega),
		(1.0 + cos_omega) / 2.0
	};
	double a[3] = {
		1.0 + alpha,
		-2.0 * cos_omega,
		1.0 - alpha
	};

	int n;
	double y, y1, y2;
	double x, x1, x2;

	x1 = 0.0;
	x2 = 0.0;
	y1 = 0.0;
	y2 = 0.0;

	for(n = 0; n < len; n++){
		fread(&x, sizeof(double), 1, f1);
		y = (b[0] / a[0]) * x + (b[1] / a[0]) * x1 + (b[2] / a[0]) * x2- (a[1] / a[0]) * y1 - (a[2] / a[0]) * y2;
		fwrite(&y, sizeof(double), 1, f2);

		x2 = x1;
		x1 = x;
		y2 = y1;
		y1 = y;
	}

	fclose(f1);
	fclose(f2);

	return 0;
}

