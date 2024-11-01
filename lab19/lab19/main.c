#include <stdio.h>
#include <stdlib.h>

void printarr(int arr[], int len) {
	printf("[");
	for (int i = 0; i < len; i++) {
		printf("%d, ", arr[i]);
	}
	printf("\b\b]\n");
}

int load(int** parr) {
	FILE* file = fopen("data.txt", "r");
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

	return len;
}

int main() {
	int* parr;
	int len;
	len = load(&parr);
	printarr(parr, len);
	return 0;
}