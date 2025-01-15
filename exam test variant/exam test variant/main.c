#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>

int N1;
int N2;
int M2;

#define MAX_N2 20
#define MAX_M2 20

int A1[20];
int A2[MAX_N2][MAX_M2];

void loadLists(char filepath[])
{
	FILE* fin = fopen(filepath, "r");

	if (fin == NULL) {
		printf("File didn't open!\n");
		return;
	}

	fscanf(fin, "%d", &N1);

	for (int i = 0; i < N1; i++) {
		fscanf(fin, "%d", &A1[i]);
	}

	fscanf(fin, "%d", &N2);
	fscanf(fin, "%d", &M2);

	for (int n = 0; n < N2; n++) {
		for (int m = 0; m < M2; m++) {
			fscanf(fin, "%d", &A2[n][m]);
		}
	}

	fclose(fin);
}

void saveLists(char filepath[])
{
	FILE* fout = fopen(filepath, "w");
	if (fopen == NULL) {
		printf("File didn't create!\n");
		return;
	}

	fprintf(fout, "%d\n", N1);
	for (int i = 0; i < N1; i++) {
		fprintf(fout, "%d ", A1[i]);
	}
	fprintf(fout, "\n");

	fprintf(fout, "%d %d\n", N2, M2);

	for (int n = 0; n < N2; n++) {
		for (int m = 0; m < M2; m++) {
			fprintf(fout, "%d ", A2[n][m]);
		}
		fprintf(fout, "\n");
	}

	fclose(fout);
}

void printLists()
{
	printf("===== Текущее состояние массивов =====\n");
	printf("A1[%d]: ", N1);
	for (int i = 0; i < N1; i++) {
		printf("%d ", A1[i]);
	}
	printf("\n\n");

	printf("A2[%d][%d]:\n", N2, M2);
	for (int n = 0; n < N2; n++) {
		for (int m = 0; m < M2; m++) {
			printf("%2d ", A2[n][m]);
		}
		printf("\n");
	}
	printf("=====================================\n");
}

void task2()
{
	int firstEvenId = 0;
	int lastEvenId = 0;

	for (int i = 0; i < N1; i++) {
		if (A1[i] % 2 == 0) {
			firstEvenId = i;
			break;
		}
	}

	for (int i = 0; i < N1; i++) {
		if (A1[i] % 2 == 0) {
			lastEvenId = i;
		}
	}

	for (int i = firstEvenId + 1; i < lastEvenId; i++) {
		if (A1[i] % 2 == 0) {
			A1[i] += 100;
		}
	}

	printf("> Выполнено задание 2\n");
}

void deleteRow(int row)
{
	for (int n = row; n < N2 - 1; n++) {
		for (int m = 0; m < M2; m++) {
			A2[n][m] = A2[n + 1][m];
		}
	}
	N2 -= 1;
}

void addColumn() {
	if (M2 + 1 <= MAX_M2) {
		for (int n = 0; n < N2; n++) {
			A2[n][M2] = 0;
		}
		M2++;
	}
	else {
		printf("Достигнут максимум колонок!\n");
	}
}

void insertColumn(int column) {
	if (M2 + 1 <= MAX_M2) {
		for (int n = 0; n < N2; n++) {
			for (int m = M2; m > column; m--) {
				A2[n][m] = A2[n][m - 1];
			}
		}
		for (int n = 0; n < N2; n++) {
			A2[n][column] = 0;
		}
		M2++;
	}
	else {
		printf("Достигнут максимум колонок!\n");
	}
}

void insertRow(int row) {
	if (N2 + 1 <= MAX_N2) {
		for (int n = N2; n > row; n--) {
			for (int m = 0; m < M2; m++) {
				A2[n][m] = A2[n - 1][m];
			}
		}
		for (int m = 0; m < M2; m++) {
			A2[row][m] = 0;
		}
		N2++;
	}
	else {
		printf("Достигнут максимум строк!\n");
	}
}

void task3() {
	for (int n = 0; n < N2; n++) {
		for (int m = 0; m < M2; m++) {
			if (A2[n][m] < 0) {
				deleteRow(n);
				break;
			}
		}
	}
	printf("> Выполнено задание 3\n");
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	loadLists("test.txt");
	printLists();

	task2();
	task3();

	printLists();

	saveLists("out.txt");

	return 0;
}