#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SortStringArray.h"

int main() {
	LoadWords("TextMarkup/dict4.txt");

	int iter = 3;
	clock_t start = clock();
	for (int i = 0; i < iter; i++) {
		CopyWordsToA();
		//memcpy(a, words, sizeof(words));

		//SelectionSortStrings();
		//QuickSortStrings();
		MergeSortStrings(a, 0, MAX_WORDS-1);

		if (!ArraysAreEqual()) {
			printf("Arrays are not equal!!!\n");
		}
		if (!isSortedStringArray(a)) {
			printf("Array is not sorted!!!\n");
		}
	}
	double runtime = (double)(clock() - start) / (double)CLOCKS_PER_SEC;
	printf_s("full time = %.3lf seconds\n", runtime);
	printf_s("single sort time = %.3lf seconds\n", runtime / iter);

	return 0;
}
