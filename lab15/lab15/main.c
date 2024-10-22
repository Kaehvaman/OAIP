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
		printf("Достигнут максимум колонок!\n");
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
		printf("Достигнут максимум колонок!\n");
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
		printf("Достигнут максимум строк!\n");
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
		puts("Невозможно открыть файл");
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
		puts("Невозможно открыть файл");
		return;
	}

	fscanf_s(fin, "%d%d", &m, &n);
	if (m > MAX_M || n > MAX_N) {
		printf("Слишком большой массив в файле!");
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
		printf("Содержимое массива:\n");
		printarr(arr);
		puts("Выберите программу");
		puts("1) Заполнение значениями i * 10 + j");
		puts("2) Заполнение нулями");
		puts("3) Заполнение случайными числами от 0 до 9");
		puts("4) Найти минимальный элемент");
		puts("5) Удалить строку");
		puts("6) Добавить пустую колонку");
		puts("7) Все нечетные увеличить в 10 раз");
		puts("8) Все кратные 10 уменьшить в 10 раз");
		puts("9) Ввести массив с клавиатуры");
		puts("10) Сохранить в файл");
		puts("11) Загрузить из файла");
		puts("12) Вставить пустую колонку");
		puts("13) Продублировать заданный столбец массива");
		puts("14) Обнулить элементы тех строк, в которых встречается более двух нулевых элементов");
		puts("15) Продублировать те строки, в которых встречаются нулевые элементы");
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
			findMin();
			break;
		case 5:
			printf("Какую строку удалить: ");
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
			printf("На каком индексе вставить колонку: ");
			scanf_s("%d", &tmp);
			insertColumn(tmp);
			break;
		case 13:
			printf("На каком индексе одублировать столбец: ");
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
			puts("Досвидания :3");
			break;
		default:
			puts("Ошибка: неправильное N");
			break;
		}
	} while (n != 0);
	return 0;
}