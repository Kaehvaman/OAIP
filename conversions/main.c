#include <stdio.h>
#include <math.h>

int main() {
	double n = 0.33;
	double sum = 0;
	int base = 8;
	for (int i = 0; i < 10; i++) {
		printf_s("%d", (int)(n * base));
		sum += (int)(n * base) * pow(base, -1 - i);
		n = n * base - (int)(n * base);
	}
	printf_s("\n%lf", sum);
	return 0;
}