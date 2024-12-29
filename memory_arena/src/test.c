#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "memory_arena.h"


int main() {

	Arena arena = ArenaInit(1024 * 1024 * 1024);
	
	char* str1 = ArenaAllocAligned(&arena, 5, sizeof(char));
	strcpy(str1, "Hell");
	printf("%s\n", str1);

	int* int2 = ArenaAllocAligned(&arena, 2 * sizeof(int), sizeof(int));
	int2[0] = 123;
	int2[1] = 789;
	printf("%d %d\n\n", int2[0], int2[1]);

	for (int i = 0; i < 16; i++) {
		printf("%2d) %d\n", i, *((char*)(arena.buffer) + i));
	}

	if (scanf("%s", str1)) {
		ArenaDestroy(&arena);
	}

	scanf("%s", str1);

	return 0;
}