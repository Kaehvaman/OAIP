#include <stdio.h>
#include <stdlib.h>

void printarr(int arr[], int len) {
	printf("[");
	for (int i = 0; i < len; i++) {
		printf("%d, ", arr[i]);
	}
	printf("\b\b]\n");
}

int load(int** parr, char filename[]) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		puts("Файл не найден");
		exit(EXIT_FAILURE);
	}

	int len = 1;
	fscanf_s(file, "%d", &len);

	*parr = (int*)malloc(sizeof(int) * len);
	if (*parr == NULL) {
		printf_s("Not enough memory to load data\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < len; i++) {
		fscanf_s(file, "%d", (*parr + i));
	}

	fclose(file);

	return len;
}

void save(int arr[], int len, char filename[]) {
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		puts("Не удалось создать файл");
		exit(EXIT_FAILURE);
	}

	fprintf_s(file, "%d\n", len);

	for (int i = 0; i < len; i++) {
		fprintf_s(file, "%d ", arr[i]);
	}

	fclose(file);
}

void saveRandomArray(int len, char filename[]) {
	int* parr;
	parr = (int*)malloc(sizeof(int) * len);
	if (parr == NULL) {
		printf_s("Not enough memory to load data\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < len; i++) {
		parr[i] = rand() % 6;
	}

	save(parr, len, filename);
}

int main() {
	int* parr;
	int len;
	//saveRandomArray(30, "data.txt");
	len = load(&parr, "data.txt");

	printarr(parr, len);
	return 0;
}