#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SortStringArray.h"

int main() {
	LoadWords("/TextMarkup/dict0.txt");

	

	for (int i = 0; i < 1; i++) {
		CopyWordsToA();

		clock_t start = clock();

		SelectionSortStrings();
		//QuickSortStrings();

		printf_s("time = %.3lf seconds", (double)(clock() - start) / (double)CLOCKS_PER_SEC);
		

		if (!ArraysAreEqual()) {
			printf("Arrays are not equal!!!\n");
		}
		if (!isSortedStringArray(a)) {
			printf("Array is not sorted!!!\n");
		}
	}

	
	return 0;
}
