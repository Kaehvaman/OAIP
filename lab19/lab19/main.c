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
	char filename[] = "in4.txt";

	int* parr;
	parr = (int*)malloc(sizeof(int) * len);
	if (parr == NULL) {
		printf_s("Not enough memory\n");
		exit(EXIT_FAILURE);
	}
	
	for (int i = 0; i < len; i++) {
		parr[i] = rand() % 200 * 1000;
	}

	save(parr, len, filename);

	free(parr);
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
	parr = (int*)malloc(sizeof(int) * (count + 1));
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

	free(parr);
}

void task3() {
	int* arr;
	int len = load(&arr, "in3.txt");

	int sum = 0;
	for (int i = 0; i < len; i++) {
		sum += arr[i];
	}
	double average = (double)sum / len;

	int count = 0;
	for (int i = 0; i < len; i++) {
		if ((arr[i] > 0) && (arr[i] < average)) count++;
	}

	if (count == 0) {
		puts("no temp that is > 0 and < average, exiting task3()");
		free(arr);
		return;
	}

	int* parr;
	parr = (int*)malloc(sizeof(int) * (count + 2));
	if (parr == NULL) {
		printf_s("Not enough memory\n");
		exit(EXIT_FAILURE);
	}
	
	int j = 0;
	for (int i = 0; i < len; i++) {
		if ((arr[i] > 0) && (arr[i] < average)) {
			parr[j] = arr[i];
			j++;
		}
	}

	save(parr, count, "out3.txt");

	free(arr);
	free(parr);
}

void task4() {
	int* pdata;
	int len = load(&pdata, "in4.txt");

	int max = pdata[0];
	for (int i = 0; i < len; i++) {
		if (pdata[i] > max) max = pdata[i];
	}

	int* pout = (int*)malloc(sizeof(int) * len);
	if (pout == NULL) {
		puts("Out of memory");
		exit(EXIT_FAILURE);
	}

	double high = (double)max * 0.667;
	int count = 0;
	for (int i = 0; i < len; i++) {
		if (pdata[i] >= high) {
			pout[count] = pdata[i];
			count++;
		}
	}

	save(pout, count, "out4.txt");

	free(pdata);
	free(pout);
}

int main() {
	//saveRandomArray();
	
	// task 1
	/*int fixarr[1000];
	int flen = loadToFixedArray(fixarr, 1000, "data.txt");
	dotasks12(fixarr, flen);*/

	// task 2
	//int* parr;
	//int len = load(&parr, "data.txt");
	//dotasks12(parr, len);
	//printarr(parr, len);
	//free(parr);
	//parr = NULL;

	//task3();

	//task4();

	return 0;
}