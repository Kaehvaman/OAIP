#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SortStringArray.h"

void printStrings(char arr[MAX_WORDS][MAX_LEN_WORD]) {
	printf("-----------\n");
	for (int i = 0; i < MAX_WORDS; i++) {
		if (1 || arr[i][0] != '\0') {
			printf("%s\n", arr[i]);
		}
	}
	printf("-----------\n");
}

int iter = 10;
char sort_funcs[][MAX_LEN_WORD] = { "SelectionSortStrings", "BubbleSortStrings", "InsertionSortStrings", "QuickSortStrings", "MergeSortStrings", "ShellSort" };

void check() {
	if (!ArraysAreEqual()) {
		printf("Arrays are not equal!!!\n");
	}
	if (!isSortedStringArray(a)) {
		printf("Array is not sorted!!!\n");
	}
	printStrings(words);
	printStrings(a);
}

void selsort() {
	clock_t start = clock();
	for (int i = 0; i < iter; i++) {
		CopyWordsToA();
		SelectionSortStrings();
		//check();
	}
	printf("%s\n", sort_funcs[0]);
	double runtime = (double)(clock() - start) / (double)CLOCKS_PER_SEC;
	printf_s("full time = %.10lf seconds\n", runtime);
	printf_s("single sort time = %.10lf seconds\n", runtime / (double)iter);
}

void bubsort() {
	clock_t start = clock();
	for (int i = 0; i < iter; i++) {
		CopyWordsToA();
		
		BubbleSortStrings();
		
		//check();
	}
	printf("%s\n", sort_funcs[1]);
	double runtime = (double)(clock() - start) / (double)CLOCKS_PER_SEC;
	printf_s("full time = %.10lf seconds\n", runtime);
	printf_s("single sort time = %.10lf seconds\n", runtime / (double)iter);
}

void inssert() {
	clock_t start = clock();
	for (int i = 0; i < iter; i++) {
		CopyWordsToA();
		InsertionSortStrings();
		//check();
	}
	printf("%s\n", sort_funcs[2]);
	double runtime = (double)(clock() - start) / (double)CLOCKS_PER_SEC;
	printf_s("full time = %.10lf seconds\n", runtime);
	printf_s("single sort time = %.10lf seconds\n", runtime / (double)iter);
}

void quicksort() {
	clock_t start = clock();
	for (int i = 0; i < iter; i++) {
		CopyWordsToA();
		QuickSortStrings();
		
		//check();
	}
	printf("%s\n", sort_funcs[3]);
	double runtime = (double)(clock() - start) / (double)CLOCKS_PER_SEC;
	printf_s("full time = %.10lf seconds\n", runtime);
	printf_s("single sort time = %.10lf seconds\n", runtime / (double)iter);
}

void mergesort() {
	clock_t start = clock();
	for (int i = 0; i < iter; i++) {
		CopyWordsToA();
		MergeSortStrings(a, 0, n - 1);
		
		//check();
	}
	printf("%s\n", sort_funcs[4]);
	double runtime = (double)(clock() - start) / (double)CLOCKS_PER_SEC;
	printf_s("full time = %.10lf seconds\n", runtime);
	printf_s("single sort time = %.10lf seconds\n", runtime / (double)iter);
}

void shellsort() {
	clock_t start = clock();
	for (int i = 0; i < iter; i++) {
		CopyWordsToA();
		
		ShellSort();
		//check();
	}
	printf("%s\n", sort_funcs[5]);
	double runtime = (double)(clock() - start) / (double)CLOCKS_PER_SEC;
	printf_s("full time = %.10lf seconds\n", runtime);
	printf_s("single sort time = %.10lf seconds\n", runtime / (double)iter);
}

int main() {
	char filename[] = "TextMarkup/dict4b.txt";
	LoadWords(filename);
	printf("%s\n\n", filename);

	selsort();
	bubsort();
	inssert();
	quicksort();
	mergesort();
	shellsort();

	printf("\a");

	return 0;
}
