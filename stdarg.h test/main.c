#include <stdio.h>
#include <stdarg.h>

void test(int n, ...) {
	printf("print doubles\n");
	va_list ar;
	va_start(ar, n);
	double val;
	for (int i = 0; i < n; i++) {
		val = va_arg(ar, double);
		printf("%.10f\n", val);
	}
	va_end(ar);
}

int main() {
	//test(4, 2.066785604F, 2.066785604, 3.14F, 3.14);
	printf("%.40f\n%.40f\n%.40f\n%.40f\n", 2.066785604F, 2.066785604, 3.14F, 3.14);
	//PrintFloats(3, 2, 4, 5);
	return 0;
}
