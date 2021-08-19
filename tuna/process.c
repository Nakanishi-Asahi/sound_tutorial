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

	double b1[3] = {
		1.53512485958697,
		-2.69169618940638,
		1.19839281085285
	};
	double a1[2] = {
		-1.69065929318241,
		0.73248077421585
	};

	double b2[3] = {
		1.0,
		-2.0,
		1.0
	};
	double a2[2] = {
		-1.99004745483398,
		0.99007225036621
	};

	int n;
	double y1, x1;
	double tmp1;
	double delay11, delay12;

	double y2, x2;
	double tmp2;
	double delay21, delay22;

	delay11 = 0.0;
	delay12 = 0.0;
	delay21 = 0.0;
	delay22 = 0.0;

	for(n = 0; n < len; n++){
		fread(&x1, sizeof(double), 1, f1);
		tmp1 = x1 - a1[0] * delay11 - a1[1] * delay12;
		y1 = b1[0] * tmp1 + b1[1] * delay11 + b1[2] * delay12;
		delay12 = delay11;
		delay11 = tmp1;

		x2 = y1;

		tmp2 = x2 - a2[0] * delay21 - a2[1] * delay22;
		y2 = b2[0] * tmp2 + b2[1] * delay21 + b2[2] * delay22;
		delay22 = delay21;
		delay21 = tmp2;
		fwrite(&y2, sizeof(double), 1, f2);
	}

	fclose(f1);
	fclose(f2);

	return 0;
}

