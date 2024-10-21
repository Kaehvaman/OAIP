#include <stdio.h>


void print1_10() {
	int i = 1;
	do {
		printf("%d ", i);
		i++;
	} while (i <= 10);
	puts("\n");
}

void print10_1() {
	int i = 10;
	do {
		printf("%d ", i);
		i--;
	} while (i >= 0);
	puts("\n");
}

void print5odd() {
	int i = 1;
	int n = 1;
	do {
		printf("%d", n);
		n += 2;
		i++;
	} while (i <= 5);
	puts("\n");
}

void print100_10() {
	int n = 100;
	while (n >= 10) {
		printf_s("%d ", n);
		n = n - 10;
	}
	puts("\n");
}

void print1000_100() {
	int n = 1000;
	while (n >= 100) {
		printf_s("%d ", n);
		n = n - 100;
	}
	puts("\n");
}

void printNfacts(int n) {
	int a = 1;
	int count = 1;
	while (n >= count) {
		printf("%d ", a);
		count++;
		a = a * count;
	}
	puts("\n");
}

void fibonacci() {
	int n;
	printf("num of fibonacchi numbers = ");
	scanf_s("%d", &n);

	long double a = 0.0;
	long double b = 1.0;
	long double c;
	n = n - 2;

	if (n <= 0) {
		puts("wrong number");
		return 0;
	}

	printf("0\n1\n");

	do {
		c = a + b;
		a = b;
		b = c;
		printf("%.0Lf\n", c);
		n = n - 1;
	} while (n > 0);
	puts("\n");
}

void prime_of_n() {
	int n;
	printf("N = ");
	scanf_s("%d", &n);
	
	int d = 2;
	while (n > 1) {
		if (n % d == 0) {
			printf("%d ", d);
			n = n / d;
		} else d++;
	}
	puts("\n");
}

int main() {
	int n, num;
	do {
		puts("choose program");
		puts("1) print 1 -> 10");
		puts("2) print 10 -> 1");
		puts("3) print first five odd numbers");
		puts("11) print 100 90 ... 10");
		puts("12) print 1000 900 ... 100");
		puts("21) print first N factorials");
		puts("55) print fibonacci numbers");
		puts("4) prime factorization of N");
		puts("");
		puts("0) exit program");

		scanf_s("%d", &n);
		puts("");
		switch (n)
		{
		case 1:
			print1_10();
			break;
		case 2:
			print10_1();
			break;
		case 3:
			print5odd();
			break;
		case 11:
			print100_10();
			break;
		case 12:
			print1000_100();
			break;
		case 21:
			printf("N = ");
			scanf_s("%d", &num);
			printNfacts(num);
		case 55:
			fibonacci();
			break;
		case 4:
			prime_of_n();
		}

	} while (n != 0);
	return 0;
}