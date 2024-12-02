#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include "../progressbar test/progressbar.h"

// \033[ = CSI, CSI ?25l hides the cursor, CSI ?25h shows the cursor
// see ANSI escape code wiki for more info
#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"

void wait(int seconds) {
	clock_t t0 = clock();
	clock_t t1;
	while ((int)(((t1 = clock()) - t0) / CLOCKS_PER_SEC) < seconds) {
		Sleep(50);
	}
	printf(" wait for %d s is over, clock=%d", seconds, (int)t1);
}

int main() {

	#ifdef WIN32
	printf("ITS WINDOWS!\n");
	#endif
	
	struct progressbar pb;
	int n = 5, sl = 1;
	printf(HIDE_CURSOR); 
	progressbar_start(&pb, n * sl);
	
	clock_t start = clock();
	
	for (int i = 0; i < n; i++) {
		wait(sl);
		//printf("%d\n", i);
		progressbar_add(&pb, sl);
	}
	//progressbar_clear();
	printf(SHOW_CURSOR);
	printf("\n");
	printf_s("time = %.3lf seconds\nexpected %d seconds\n", (double)(clock() - start) / (double)CLOCKS_PER_SEC, n * sl);
	
	progressbar_start(&pb, n * sl);
	for (int i = 0; i < n; i++) {
		wait(sl);
		//printf("%d\n", i);
		progressbar_add(&pb, sl);
	}
	return 0;
}