#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <Windows.h>


int main() {
	int n = 10, sl = 10, last_clock = 0;
	clock_t start = clock();
	for (int i = 0; i < n; i++) {
		printf_s("%d\n", i);
		Sleep(sl);
	}
	printf_s("time = %.3lf seconds\nexpected %d seconds %lf", (double)(clock() - start) / (double)CLOCKS_PER_SEC, n * sl / 1000, 0.3300000000000000000000);
	return 0;
}