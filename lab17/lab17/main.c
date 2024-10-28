#include <stdio.h>

long long fact(int n) {
	if (n == 0) {
		return 1;
	}
	printf_s("n=%d\n", n);
	long long res = fact(n - 1) * n;
	printf_s("n=%d fact(%d)=%lld res=%lld\n", n, n - 1, res / n, res);
	return res;
}

void f1(int n, FILE* f) {
	printf_s("%d ", n);
	fprintf(f, "f1(%d) -> print(%d) \n", n, n);
	if (n > 1) {
		f1(n - 2, f);
		fprintf(f, "f1(%d) returned \n", n - 2);
	}
}

void f2(int n, FILE* f) {
	if (n > 1) {
		f2(n - 2, f);
		fprintf(f, "f2(%d) returned \n", n - 2);
	}
	printf_s("%d ", n);
	fprintf(f, "f2(%d) -> print(%d) \n", n, n);
}

void f3(int n, FILE* f) {
	printf_s("%d ", n);
	fprintf(f, "f3(%d) -> print(%d) \n", n, n);
	if (n > 3) {
		f3(n - 2, f);
		fprintf(f, "f3(%d) returned \n", n - 2);
	}
	if (n == 3) {
		printf_s("1 ");
		fprintf(f, "f3(%d) && n == 3 -> print(%d) \n", n, 1);
	}
	printf_s("%d ", n);
	fprintf(f, "f3(%d) -> print(%d) \n", n, n);
}

void recEGE1(int n, FILE* f) {
	if (n >= 1) {
		printf(" %d", n);
		fprintf(f, "recEGE1(%d) && (n >= 1) == true -> print( %d) \n", n, n);
		recEGE1(n - 1, f);
		fprintf(f, "1)recEGE1(%d) returned\n", n - 1);
		recEGE1(n - 1, f);
		fprintf(f, "2)recEGE1(%d) returned \n", n - 1);
	}
}

void F1(int n, FILE* f) {
	if (n > 2) {
		printf_s("%d\n", n);
		fprintf(f, "F1(%d) -> print(%d) \n", n, n);
		F1(n - 3, f);
		fprintf(f, "1)F1(%d) returned\n", n - 3);
		F1(n - 4, f);
		fprintf(f, "2)F1(%d) returned\n", n - 4);
	}
}

void F2(int n, FILE* f) {
	if (n < 5) {
		printf_s("%d\n", n);
		fprintf(f, "F2(%d) -> print(%d) \n", n, n);
		F2(n + 1, f);
		fprintf(f, "1)F2(%d) returned\n", n + 1);
		F2(n + 3, f);
		fprintf(f, "2)F2(%d) returned\n", n + 3);
	}
}

void G3(int n, FILE* f);

void F3(int n, FILE* f) {
	if (n > 0) {
		G3(n - 1, f);
		fprintf(f, "G3(%d) returned\n", n - 1);
	}
}

void G3(int n, FILE* f) {
	printf_s("*");
	fprintf(f, "G3(%d) -> print(*) \n", n);
	if (n > 1) {
		F3(n - 3, f);
		fprintf(f, "F3(%d) returned\n", n - 3);
	}
}

int main() {
	FILE* fout = fopen("trace.txt", "w");
	if (fout == NULL) {
		puts("Невозможно создать файл");
		return;
	}

	//printf("%lld", fact(5)); // 1

	f1(11, fout);
	fprintf(fout, "f1(%d) returned\n", 11);

	fprintf(fout, "\n");
	printf_s("\n\n");
	f2(11, fout);
	fprintf(fout, "f2(%d) returned\n", 11);

	fprintf(fout, "\n");
	printf_s("\n\n");
	f3(11, fout);
	fprintf(fout, "f3(%d) returned\n", 11);

	fprintf(fout, "\n");
	printf_s("\n\n");
	recEGE1(3, fout);
	fprintf(fout, "recEGE1(%d) returned\n", 3);

	fprintf(fout, "\n");
	printf_s("\n\n");
	F1(10, fout);
	fprintf(fout, "F1(%d) returned\n", 10);

	fprintf(fout, "\n");
	printf_s("\n\n");
	F2(1, fout);
	fprintf(fout, "F2(%d) returned\n", 1);

	fprintf(fout, "\n");
	printf_s("\n\n");
	F3(11, fout);
	fprintf(fout, "F3(%d) returned\n", 11);

	fclose(fout);
	return 0;
}