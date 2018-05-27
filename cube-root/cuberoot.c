#include <stdio.h>
#include <math.h>

int main() {
	double x, y[2];
	unsigned long int i = 0;
	
	printf("x -> ");
	scanf("%lf", &x);

	printf("y[%lu]=%f\n", i++, x);
	y[1] = x;
	do {
		y[0] = y[1];
		
		//y[1] = y[0] + 0.5 * (y[0] - pow(y[0], 3) / x);
		y[1] = 0.5 * (y[0] + 3 * x / (2 * pow(y[0], 2) + x / y[0]));
		
		printf("y[%lu]=%f\n", i++, y[1]);
		printf("\tdiff = %f\n", fabs(y[1] - y[0]));

	} while (fabs(y[1] - y[0]) >= 2e-6);
	
	return 0;
}

