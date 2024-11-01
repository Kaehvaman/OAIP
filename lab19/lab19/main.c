#include <stdio.h>
#include <stdlib.h>

void printarr(int arr[], int len) {
	printf("[");
	for (int i = 0; i < len; i++) {
		printf("%d, ", arr[i]);
	}
	printf("\b\b]\n");
}

int loadToFixedArray(int arr[], int len, char filename[]) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		puts("File not found");
		exit(EXIT_FAILURE);
	}

	int flen;
	fscanf_s(file, "%d", &flen);
	if (flen > len) {
		puts("Dataset if too big");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < flen; i++) {
		fscanf_s(file, "%d", &arr[i]);
	}

	fclose(file);

	return flen;
}

int load(int** parr, char filename[]) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		puts("File not found");
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
		puts("Failed to create file");
		exit(EXIT_FAILURE);
	}

	fprintf_s(file, "%d\n", len);

	for (int i = 0; i < len; i++) {
		fprintf_s(file, "%d ", arr[i]);
	}

	fclose(file);
}

void saveRandomArray() {
	int len = 1000;
	char filename[] = "out3.txt";

	int* parr;
	parr = (int*)malloc(sizeof(int) * len);
	if (parr == NULL) {
		printf_s("Not enough memory\n");
		exit(EXIT_FAILURE);
	}
	
	for (int i = 0; i < len; i++) {
		parr[i] = rand() % 60 - 30;
	}

	save(parr, len, filename);
}

void dotasks12(int arr[], int len) {
	int sum = 0;
	for (int i = 0; i < len; i++) {
		sum += arr[i];
	}
	int average = sum / len;

	int count = 0;
	for (int i = 0; i < len; i++) {
		if (arr[i] > average) count++;
	}

	int* parr;
	parr = (int*)malloc(sizeof(int) * count);
	if (parr == NULL) {
		printf_s("Not enough memory\n");
		exit(EXIT_FAILURE);
	}

	int j = 0;
	for (int i = 0; i < len; i++) {
		if (arr[i] > average) {
			parr[j] = arr[i];
			j++;
		}
	}

	save(parr, count, "tasks12.txt");
}

int main() {
	saveRandomArray();

	// task 2
	//int* parr;
	//int len = load(&parr, "data.txt");
	//dotasks12(parr, len);
	//printarr(parr, len);


	// task 1
	/*int fixarr[1000];
	int flen = loadToFixedArray(fixarr, 1000, "data.txt");
	dotasks12(fixarr, flen);*/

	return 0;
}