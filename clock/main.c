#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <stdlib.h>
#include "../progressbar test/progressbar.h"

// \033[ = CSI, CSI ?25l hides the cursor, CSI ?25h shows the cursor
// see ANSI escape code wiki for more info
#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"

void wait(int seconds) {
	clock_t t0 = clock();
	clock_t t1;
	while ((int)(((t1 = clock()) - t0) / CLOCKS_PER_SEC) < seconds) {
		Sleep(1000);
	}
	printf(" wait for %d s is over, clock=%d", seconds, (int)t1);
}

int main(int argc, char* argv[]) {

	#ifdef WIN32
	printf("ITS WINDOWS!\n");
	#endif

	for (int i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}

	struct progressbar pb;
	int n = 1, sl = 1;
	printf(HIDE_CURSOR);
	printf("\033[385;31m");
	progressbar_start(&pb, n * sl);
	
	clock_t start = clock();
	
	for (int i = 1; i <= n; i++) {
		int percentage = 100 * i / n;
		if (percentage < 33) {
			printf("\033[385;31m");
		}
		else if (33 < percentage && percentage < 66) {
			printf("\033[385;33m");
		}
		else {
			printf("\033[385;32m");
		}
		wait(sl);
		//printf("%d\n", i);
		progressbar_add(&pb, sl);
	}
	//progressbar_clear();
	printf("\033[0m");
	printf(SHOW_CURSOR);
	printf("\n");
	printf_s("time = %.3lf seconds\nexpected %d seconds\n", (double)(clock() - start) / (double)CLOCKS_PER_SEC, n * sl);

	int count = 0;
	for (int i = 40; i <= 47; i++) {
		printf("\033[385;%dm", i);
		for (int j = 30; j <= 37; j++) {
			printf("\033[385;%dm", j);
			printf("%02X ", count);
			count++;
		}
		for (int j = 90; j <= 97; j++) {
			printf("\033[385;%dm", j);
			printf("%02X ", count);
			count++;
		}
		printf("\n");
	}
	for (int i = 100; i <= 107; i++) {
		printf("\033[385;%dm", i);
		for (int j = 30; j <= 37; j++) {
			printf("\033[385;%dm", j);
			printf("%02X ", count);
			count++;
		}
		for (int j = 90; j <= 97; j++) {
			printf("\033[385;%dm", j);
			printf("%02X ", count);
			count++;
		}
		printf("\n");
	}
	printf("\033[0m");
	printf("\n");

	count = 0;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			printf("\033[48;5;%dm", count);
			printf("%02X ", count);
			count++;
		}
		printf("\033[48;5;0m");
		printf("#\n");
	}
	printf("\033[48;5;0m");
	printf("\n");

	return 0;
}