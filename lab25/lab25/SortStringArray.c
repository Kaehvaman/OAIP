#include "SortStringArray.h"

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
			return 0;
		}
	}

	return 1;
}

void swapWords(char a[], char b[]) {
	char tmp[MAX_LEN_WORD];
	strcpy(tmp, a);
	strcpy(a, b);
	strcpy(a, tmp);
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
	while (i < MAX_WORDS) {
		int j = i;
		while (j > 0 && strcmp(a[j - 1], a[j]) > 0) {
			swapWords(a[j], a[j - 1]);
			j -= 1;
		}
		i += 1;
	}
}

/**
 * Сортирует массив, используя рекурсивную сортировку слиянием
 * up - указатель на массив, который нужно сортировать
 * down - указатель на массив с, как минимум, таким же размером как у 'up', используется как буфер
 * left - левая граница массива, передайте 0, чтобы сортировать массив с начала
 * right - правая граница массива, передайте длину массива - 1, чтобы сортировать массив до последнего элемента
 * возвращает: указатель на отсортированный массив. Из-за особенностей работы данной реализации
 * отсортированная версия массива может оказаться либо в 'up', либо в 'down'
 **/
char* MergeSortStrings(char* up, char* down, unsigned int left, unsigned int right) {

	if (left == right)
	{
		strcpy(down[left], up[left]);
		return down;
	}

	unsigned int middle = left + (right - left) / 2;

	// разделяй и сортируй
	char* l_buff = MergeSortStrings(up, down, left, middle);
	char* r_buff = MergeSortStrings(up, down, middle + 1, right);

	// слияние двух отсортированных половин
	char* target = (l_buff == up) ? down : up;

	unsigned int l_cur = left, r_cur = middle + 1;
	for (unsigned int i = left; i <= right; i++)
	{
		if (l_cur <= middle && r_cur <= right)
		{
			if (strcmp(l_buff[l_cur], r_buff[r_cur]) < 0)
			{
				strcpy(target[i], l_buff[l_cur]);
				l_cur++;
			}
			else
			{
				strcpy(target[i], r_buff[r_cur]);
				r_cur++;
			}
		}
		else if (l_cur <= middle)
		{
			strcpy(target[i], l_buff[l_cur]);
			l_cur++;
		}
		else
		{
			strcpy(target[i], r_buff[r_cur]);
			r_cur++;
		}
	}
	return target;
}

void ShellSort(char* array, int size) {
	for (int s = size / 2; s > 0; s /= 2) {
		for (int i = s; i < size; ++i) {
			for (int j = i - s; j >= 0 && strcmp(array[j], array[j + s]) > 0; j -= s) {
				char tmp[MAX_LEN_WORD];
				strcpy(tmp, array[j]);
				strcpy(array[j], array[j + s]);
				strcpy(array[j + s], tmp);
			}
		}
	}
}
