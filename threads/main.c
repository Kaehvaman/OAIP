#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <iso646.h>
#include <string.h>

#include <threads.h>

int thrd_func(void* i) {
	int* arg_ptr = (int*)i;

	unsigned long long y = 1;
	for (unsigned long long x = 0; x < 1000ULL * 1000 * 1000 * 10; x++) {
		y += x;
	}

	printf("lol %d) y=%llu\n", *arg_ptr, y);
	return *arg_ptr;
}

int main() {
	thrd_t threads[10];
	int args[10];
	int results[10];
	for (int i = 0; i < 10; i++) {
		args[i] = i;
		thrd_create(&threads[i], thrd_func, &args[i]);
		printf("%d) thread created\n", i);
	}
	printf("-----------\n");
	for (int i = 0; i < 10; i++) {
		thrd_join(threads[i], &results[i]);
	}

	return 0;
}