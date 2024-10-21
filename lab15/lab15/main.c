#include <stdio.h>
#include <stdlib.h> 
#include <Windows.h>

#define MAX_M 6
#define MAX_N 6

int m = 3;
int n = 3;

int arr[MAX_M][MAX_N] = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
};

void printarr() {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("%2d ", arr[i][j]);
		}
		printf("\n");
	}
}

void fill_with_indexes() {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			arr[i][j] = (i * 10) + j;
		}
	}
}

void fillZero() {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			arr[i][j] = 0;
		}
	}
}

void fillRand() {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			arr[i][j] = rand() % 10;
		}
	}
}

void findMin() {
	int min = arr[0][0];
	int iMin = 0;
	int jMin = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] < min) {
				printf("min = %d\n", arr[i][j]);
				printf("imin = %d\n", i);
				printf("jmin = %d\n", j);
			}
		}
	}
	
}


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int n = 0;
	do {
		puts("\n");
		printf("Содержимое массива:\n");
		printarr(arr);
		puts("Выберите программу");
		puts("1) Заполнение значениями i * 10 + j");
		puts("2) Заполнение нулями");
		puts("3) Заполнение случайными числами от 0 до 9");
		puts("4) ");
		puts("5) ");
		puts("6) ");
		puts("7) ");
		puts("99) ");
		puts("10) ");
		puts("11) ");
		puts("");
		puts("0) Выйти из программы");

		while (scanf_s(" %d", &n) != 1) {
			scanf_s("%*[^\n]");
			scanf_s("%*c");
		}
		puts("");

		switch (n)
		{
		case 1:
			fill_with_indexes();
			break;
		case 2:
			fillZero();
			break;
		case 3:
			fillRand();
			break;
		case 4:
			
			break;
		case 0:
			puts("Досвидания :3");
			break;
		default:
			puts("Ошибка: неправильное N");
			break;
		}
	} while (n != 0);
	return 0;
}