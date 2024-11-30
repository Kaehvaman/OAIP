#define _CRT_SECURE_NO_WARNINGS
#include "SortStringArray.h"

// Слова, загруженные из файла 
char words[MAX_WORDS][MAX_LEN_WORD];
// Количество слов в массиве
int n = 0;
// Массив для сортировки 
char a[MAX_WORDS][MAX_LEN_WORD];


int LoadWords(char* filename) {
	// открыть файл
	FILE* fin = fopen(filename, "r");
	if (fin == NULL) {
		// если файл не смогли открыть - сообщаем об этом
		printf("File %s can't be opened!\n", filename);
		return 0;
	}

	char token[MAX_LEN_WORD];
	int char_token;
	// пока не конец файла
	while (!feof(fin)) {
		// пока есть разделитель - берем его
		while (getNextDelim(fin, &char_token)) {
		}
		// если есть слово - берем его
		if (getNextWord(fin, token, MAX_LEN_WORD)) {
			if (n < MAX_WORDS) {
				strcpy(words[n], token);
				n++;
			}
			else {
				printf("There are more words than elements in array!!\n");
				fclose(fin);
				return 0;
			}
		}
	}
	// Закрываем файл с текстом
	fclose(fin);
	return 1;
}

void CopyWordsToA() {
	for (int i = 0; i < n; i++) {
		strcpy(a[i], words[i]);
	}
}

int ArraysAreEqual() {
	static int counts_in_words[MAX_WORDS];
	static int counts_in_a[MAX_WORDS];

	for (int i = 0; i < n; i++) {
		counts_in_words[i] = 0;
		counts_in_a[i] = 0;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (strcmp(words[i], words[j]) == 0) {
				counts_in_words[i]++;
			}
			if (strcmp(words[i], a[j]) == 0) {
				counts_in_a[i]++;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		if (counts_in_words[i] != counts_in_a[i]) {
			printf("-----------\n");
			for (int i = 0; i < MAX_WORDS; i++) {
				if (1 || a[i][0] != '\0') {
					printf("%d) %s\n", counts_in_a[i], a[i]);
				}
			}
			printf("-----------\n");
			return 0;
		}
	}

	return 1;
}

void swapWords(char a[], char b[]) {
	char tmp[MAX_LEN_WORD];
	strcpy(tmp, a);
	strcpy(a, b);
	strcpy(b, tmp);
}

int isSortedStringArray(char a[MAX_WORDS][MAX_LEN_WORD]) {
	for (int i = 0; i < n - 1; i++) {
		if (strcmp(a[i], a[i + 1]) > 0) {
			return 0;
		}
	}
	return 1;
}

int LinearSearchStrings(char target[], char source[MAX_WORDS][MAX_LEN_WORD]) {
	for (int i = 0; i < n; i++) {
		if (strcmp(target, source[i]) == 0) {
			return i;
		}
	}
	return -1;
}

int BinarySearchStrings(char target[], char source[MAX_WORDS][MAX_LEN_WORD]) {
	if (!isSortedStringArray(source)) {
		return -1;
	}

	int left = 0;
	int right = n - 1;

	while (left <= right) {
		int middle = (left + right) / 2;

		if ((strcmp(target, source[middle]) == 0)) {
			return middle;
		}
		else if (strcmp(source[middle], target) < 0) {
			left = middle + 1;
		}
		else if (strcmp(source[middle], target) > 0) {
			right = middle - 1;
		}
	}
	return -1;
}

void SelectionSortStrings() {
	for (int i = 0; i < n - 1; i++) {

		int iMin = i;
		for (int j = i + 1; j < n; j++) {
			if (strcmp(a[j], a[iMin]) < 0) {
				iMin = j;
			}
		}

		if (i != iMin) {
			swapWords(a[i], a[iMin]);
		}
	}
}

void QuickSortStrings() {
	qsort(a, n, sizeof(a[0]), strcmp);
}

void BubbleSortStrings() {
	for (int i = 0; i < n - 1; i++) {
		// Last i elements are already in place, so the loop
		// will only num n - i - 1 times
		for (int j = 0; j < n - i - 1; j++) {
			if (strcmp(a[j], a[j + 1]) > 0)
				swapWords(a[j], a[j + 1]);
		}
	}
}

void InsertionSortStrings() {
	int i = 1;
	while (i < n) {
		int j = i;
		while (j > 0 && strcmp(a[j - 1], a[j]) > 0) {
			swapWords(a[j], a[j - 1]);
			j -= 1;
		}
		i += 1;
	}
}

// Merges two subarrays of arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
void merge(char arr[MAX_WORDS][MAX_LEN_WORD], int left, int mid, int right) {
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	// Create temporary arrays
	static char leftArr[MAX_WORDS][MAX_LEN_WORD];
	static char rightArr[MAX_WORDS][MAX_LEN_WORD];

	// Copy data to temporary arrays
	for (i = 0; i < n1; i++) {
		strcpy(leftArr[i], arr[left + i]);
	}
	for (j = 0; j < n2; j++) {
		strcpy(rightArr[j], arr[mid + 1 + j]);
	}

	// Merge the temporary arrays back into arr[left..right]
	i = 0;
	j = 0;
	k = left;
	while (i < n1 && j < n2) {
		if (strcmp(leftArr[i], rightArr[j]) <= 0) {
			strcpy(arr[k], leftArr[i]);
			i++;
		}
		else {
			strcpy(arr[k], rightArr[j]);
			j++;
		}
		k++;
	}

	// Copy the remaining elements of leftArr[], if any
	while (i < n1) {
		strcpy(arr[k], leftArr[i]);
		i++;
		k++;
	}

	// Copy the remaining elements of rightArr[], if any
	while (j < n2) {
		strcpy(arr[k], rightArr[j]);
		j++;
		k++;
	}
}

// The subarray to be sorted is in the index range [left-right]
void MergeSortStrings(char arr[MAX_WORDS][MAX_LEN_WORD], int left, int right) {
	if (left < right) {

		// Calculate the midpoint
		int mid = left + (right - left) / 2;

		// Sort first and second halves
		MergeSortStrings(arr, left, mid);
		MergeSortStrings(arr, mid + 1, right);

		// Merge the sorted halves
		merge(arr, left, mid, right);
	}
}

void ShellSort() {
	for (int s = n / 2; s > 0; s /= 2) {
		for (int i = s; i < n; ++i) {
			for (int j = i - s; j >= 0 && strcmp(a[j], a[j + s]) > 0; j -= s) {
				char tmp[MAX_LEN_WORD];
				strcpy(tmp, a[j]);
				strcpy(a[j], a[j + s]);
				strcpy(a[j + s], tmp);
			}
		}
	}
}
