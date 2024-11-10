#include <stdio.h>
#include <stdlib.h>
#include <time.h>  

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
	char filename[] = "rand.txt";

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

	save(parr, count, "out12.txt");

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

void swap(int* arr, int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void bubbleSort(int arr[], int n) {
	for (int i = 0; i < n - 1; i++) {

		// Last i elements are already in place, so the loop
		// will only num n - i - 1 times
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1])
				swap(arr, j, j + 1);
		}
	}
}

void task5() {
	int* pdata;
	int len = load(&pdata, "in5.txt");

	int oddCount = 0;
	int evenCount = 0;

	for (int i = 0; i < len; i++) {
		if (pdata[i] % 2 == 0) {
			evenCount++;
		}
		else {
			oddCount++;
		}
	}

	if (oddCount == 0 || evenCount == 0) {
		puts("No odds or evens, exiting task5()");
		free(pdata);
		return;
	}

	int* peven = (int*)malloc(sizeof(int) * (evenCount + 2));
	if (peven == NULL) {
		puts("Out of memory");
		exit(EXIT_FAILURE);
	}

	int* podd = (int*)malloc(sizeof(int) * (oddCount + 2));
	if (podd == NULL) {
		puts("Out of memory");
		exit(EXIT_FAILURE);
	}

	int ieven = 0, iodd = 0;
	for (int i = 0; i < len; i++) {
		if (pdata[i] % 2 == 0) {
			peven[ieven] = pdata[i];
			ieven++;
		}
		else {
			podd[iodd] = pdata[i];
			iodd++;
		}
	}

	bubbleSort(peven, evenCount);
	bubbleSort(podd, oddCount);

	FILE* file = fopen("out5.txt", "w");
	if (file == NULL) {
		puts("Failed to create file");
		exit(EXIT_FAILURE);
	}

	fprintf_s(file, "%d\n", len);

	for (int i = 0; i < evenCount; i++) {
		fprintf_s(file, "%d ", peven[i]);
	}

	for (int i = oddCount - 1; i >= 0; i--) {
		fprintf_s(file, "%d ", podd[i]);
	}

	fclose(file);

	free(pdata);
	free(peven);
	free(podd);
}

int clip(int n, int lower, int upper) {
	return max(lower, min(n, upper));
}

void createRandomBinFiles(int n, int size) {
	if (size <= 0) {
		puts("size can't be less than 1");
		return;
	}

	for (int i = 0; i < n; i++) {
		unsigned char* pa = (int*)malloc(size);
		if (pa == NULL) {
			puts("Out of memory");
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < size; i++) {
			pa[i] = (unsigned char)rand();
		}

		char path[_MAX_PATH];
		sprintf_s(path, _MAX_PATH, "randbin\\bin%d", i);

		FILE* file = fopen(path, "wb");
		if (file == NULL) {
			puts("Failed to create file");
			exit(EXIT_FAILURE);
		}

		fwrite(pa, sizeof(unsigned char), size, file);

		fclose(file);
		free(pa);
	}
}

int main() {
	srand((unsigned int)time(NULL));

	clock_t start = clock();

	//saveRandomArray();
	
	// task 1
	/*int fixarr[1000];
	int flen = loadToFixedArray(fixarr, 1000, "in12.txt");
	dotasks12(fixarr, flen);*/

	// task 2
	//int* parr;
	//int len = load(&parr, "in12.txt");
	//dotasks12(parr, len);
	//printarr(parr, len);
	//free(parr);
	//parr = NULL;

	//task3();

	//task4();

	//task5();

	createRandomBinFiles(32, 64 * 1024 * 1024);

	printf_s("time = %.3lf seconds", (double)(clock() - start) / (double)CLOCKS_PER_SEC);

	return 0;
}