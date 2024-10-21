#include <stdio.h>
#include <stdlib.h> 
#include <Windows.h>

#define MAX_M 10
#define MAX_N 10

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

void deleteRow(int row) {
	for (int i = row; i < m - 1; i++) {
		for (int j = 0; j < n; j++) {
			arr[i][j] = arr[i + 1][j];
		}
	}
	m--;
}

void addColumn() {
	if (n + 1 <= MAX_N) {
		for (int i = 0; i < m; i++) {
			arr[i][n] = 0;
		}
		n++;
	}
	else {
		printf("��������� �������� �������!\n");
	}
}

void insertColumn(int column) {
	if (n + 1 <= MAX_N) {
		for (int i = 0; i < m; i++) {
			for (int j = n; j > column; j--) {
				arr[i][j] = arr[i][j - 1];
			}
		}
		for (int i = 0; i < m; i++) {
			arr[i][column] = 0;
		}
		n++;
	}
	else {
		printf("��������� �������� �������!\n");
	}
}

void insertRow(int row) {
	if (m + 1 <= MAX_M) {
		for (int i = m; i > row; i--) {
			for (int j = 0; j < n; j++) {
				arr[i][j] = arr[i - 1][j];
			}
		}
		for (int i = 0; i < n; i++) {
			arr[row][i] = 0;
		}
		m++;
	}
	else {
		printf("��������� �������� �����!\n");
	}
}

void odd10x() {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j] % 2 != 0) arr[i][j] *= 10;
		}
	}
}

void crat10() {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j] % 10 == 0) arr[i][j] /= 10;
		}
	}
}

void inputArr() {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("a%d%d = ", i, j);
			scanf_s("%d", &arr[i][j]);
		}
	}
}

void save() {
	FILE* fout = fopen("savefile.txt", "w");
	if (fout == NULL) {
		puts("���������� ������� ����");
		return;
	}

	fprintf(fout, "%d %d\n", m, n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			fprintf(fout, "%2d ", arr[i][j]);
		}
		fprintf(fout, "\n");
	}

	fclose(fout);
}

void load() {
	FILE* fin = fopen("savefile.txt", "r");
	if (fin == NULL) {
		puts("���������� ������� ����");
		return;
	}

	fscanf_s(fin, "%d%d", &m, &n);
	if (m > MAX_M || n > MAX_N) {
		printf("������� ������� ������ � �����!");
		return;
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			fscanf_s(fin, "%d", &arr[i][j]);
		}
	}

	fclose(fin);
}

void duplicateColumn(int column) {
	insertColumn(column);
	for (int i = 0; i < m; i++) {
		arr[i][column] = arr[i][column + 1];
	}
}

int count(int num, int arr[], int len) {
	int count = 0;
	for (int i = 0; i < len; i++) {
		if (arr[i] == num) count += 1;
	}
	return count;
}

void row0() {
	for (int i = 0; i < m; i++) {
		if (count(0, arr[i], n) > 2) {
			for (int j = 0; j < n; j++) {
				arr[i][j] = 0;
			}
		}
	}
}

void duplicateRow(int row) {
	insertRow(row);
	for (int j = 0; j < n; j++) {
		arr[row][j] = arr[row + 1][j];
	}
}

void dupRow0() {
	for (int i = 0; i < m; i++) {
		if (count(0, arr[i], n) > 0) {
			duplicateRow(i);
			i++;
		}
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int tmp;

	int n = 0;
	do {
		puts("\n");
		printf("���������� �������:\n");
		printarr(arr);
		puts("�������� ���������");
		puts("1) ���������� ���������� i * 10 + j");
		puts("2) ���������� ������");
		puts("3) ���������� ���������� ������� �� 0 �� 9");
		puts("4) ����� ����������� �������");
		puts("5) ������� ������");
		puts("6) �������� ������ �������");
		puts("7) ��� �������� ��������� � 10 ���");
		puts("8) ��� ������� 10 ��������� � 10 ���");
		puts("9) ������ ������ � ����������");
		puts("10) ��������� � ����");
		puts("11) ��������� �� �����");
		puts("12) �������� ������ �������");
		puts("13) �������������� �������� ������� �������");
		puts("14) �������� �������� ��� �����, � ������� ����������� ����� ���� ������� ���������");
		puts("15) �������������� �� ������, � ������� ����������� ������� ��������");
		puts("");
		puts("0) ����� �� ���������");

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
			findMin();
			break;
		case 5:
			printf("����� ������ �������: ");
			scanf_s("%d", &tmp);
			deleteRow(tmp);
			break;
		case 6:
			addColumn();
			break;
		case 7:
			odd10x();
			break;
		case 8:
			crat10();
			break;
		case 9:
			inputArr();
			break;
		case 10:
			save();
			break;
		case 11:
			load();
			break;
		case 12:
			printf("�� ����� ������� �������� �������: ");
			scanf_s("%d", &tmp);
			insertColumn(tmp);
			break;
		case 13:
			printf("�� ����� ������� ������������ �������: ");
			scanf_s("%d", &tmp);
			duplicateColumn(tmp);
			break;
		case 14:
			row0();
			break;
		case 15:
			dupRow0();
			break;
		case 0:
			puts("���������� :3");
			break;
		default:
			puts("������: ������������ N");
			break;
		}
	} while (n != 0);
	return 0;
}