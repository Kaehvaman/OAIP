#include <stdio.h>
#include <math.h>

int main() {
	int n;
	printf("num of fibonacchi numbers = ");
	scanf_s("%d", &n);
	
	double a = 0.0;
	double b = 1.0;
	double c;
	n = n - 2;
	
	if (n <= 0) {
		puts("wrong number");
		return 0;
	}

	printf("0\n1\n");

	do {
		c = a + b;
		a = b;
		/*if (b > c) {
			printf("overflow, remaining n = %d", n);
			break;
		}*/
		b = c;
		printf("%.0f\n", c);
		n = n - 1;
	} while (n > 0);
	
	/*puts("\n------------");
	
	if (pow(2, 64) > 12200160415121876738.0) {
		printf("%f is bigger than %f", pow(2, 64), 12200160415121876738.0);
	} else {
		puts("12200160415121876738 is bigger");
	}*/
	//printf("%u", sizeof(12200160415121876738));
	return 0;
}
