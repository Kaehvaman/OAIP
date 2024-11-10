#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

void thrd_func(int* i) {
	printf_s("%d\n", *i);
}

int main() {
	thrd_t* threads[10];
	for (int i = 0; i < 10; i++) {
		thrd_create(threads[i], thrd_func, &i);
	}
	return 0;
}