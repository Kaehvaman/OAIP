#include <stdio.h>
#include <Windows.h>


int index(int num, int arr[], int len) {
	for (int i = 0; i < len; i++) {
		if (arr[i] == num) return i;
	}
	return -1;
}

int count(int num, int arr[], int len) {
	int count = 0;
	for (int i = 0; i < len; i++) {
		if (arr[i] == num) count += 1;
	}
	return count;
}

int arrmax(int arr[], int len) {
	int max = arr[0];
	for (int i = 1; i < len; i++) {
		if (arr[i] > max) max = arr[i];
	}
	return max;
}

int arrmin(int arr[], int len) {
	int min = arr[0];
	for (int i = 1; i < len; i++) {
		if (arr[i] < min) min = arr[i];
	}
	return min;
}

void printarr(int arr[], int len) {
	printf("[");
	for (int i = 0; i < len; i++) {
		printf("%d, ", arr[i]);
	}
	printf("\b\b]\n");
}

void deleteindex(int index, int arr[], int* len) {
	arr[index] = 0;
	for (int i = index; i < *len - 1; i++) {
		arr[i] = arr[i + 1];
	}
	*len -= 1;
}

void insert(int num, int index, int arr[], int* len) {
	for (int i = *len; i > index; i--) {
		arr[i] = arr[i - 1];
	}
	*len += 1;
	arr[index] = num;
}

void deletemax3(int arr[], int* len) {
	int max = arr[0];
	int maxi = 0;
	for (int i = 1; i < *len; i++) {
		if (arr[i] > max && arr[i] % 3 == 0) {
			max = arr[i];
			maxi = i;
		}
	}
	deleteindex(maxi, arr, len);
}

exchange_max_chains(int A[], int B[], int* sA, int* sB) {
	int a = A[0], sa = 1, ai = 0;
	int b = B[0], sb = 1, bi = 0;
	int ts = 1;
	for (int i = 0; i < *sA - 1; i++) {
		if (A[i] == A[i + 1]) {
			ts += 1;
		}
		else if (ts > sa) {
			sa = ts;
			ai = i + 1 - sa;
			ts = 1;
			a = A[i];
		}
	}
	ts = 1;
	for (int i = 0; i < *sB - 1; i++) {
		if (B[i] == B[i + 1]) {
			ts += 1;
		}
		else if (ts > sb) {
			sb = ts;
			bi = i + 1 - sb;
			ts = 1;
			b = B[i];
		}
	}
	for (int i = 0; i < sa; i++) {
		deleteindex(ai, A, sA);
	}
	for (int i = 0; i < sb; i++) {
		insert(b, ai, A, sA);
	}
	for (int i = 0; i < sb; i++) {
		deleteindex(bi, B, sB);
	}
	for (int i = 0; i < sa; i++) {
		insert(a, bi, B, sB);
	}
	printf("A: %d %d %d\n", a, sa, ai);
	printf("B: %d %d %d\n", b, sb, bi);
	printf("A = ");
	printarr(A, *sA);
	printf("B = ");
	printarr(B, *sB);
}

//#define ARRLEN 10

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int arr[20] = { 3, 7, 12, 3, 4, 8, -1, 6, 1, 7 };
	int size = 10;
	int A[20] = {3, 2, 2, 5, 2, 1, 1, 1, 3, 9};
	int sA = 10;
	int B[20] = {1, 2, 5, 5, 4, 8, 3, 3};
	int sB = 8;
	int id, val;

	int n = 0;
	do {
		puts("\n");
		printf("Содержимое массива : ");
		printarr(arr, size);
		puts("Выберите программу");
		puts("1) Удалить элемент по индексу");
		puts("2) Вставить элемент по индексу");
		puts("3) Удалить минимальный элемент");
		puts("4) Перед минимальным элементом вставить 0");
		puts("5) Удалить все чётные элементы");
		puts("6) Дублировать все чётные элементы");
		puts("7) Добавить в начало элемент, равный минимальному");
		puts("99) Удалить максимальный элемент кратный трём");
		puts("10) Удалить элементы, встречающиеся в массиве только один раз");
		puts("11) Между массивами A и B обменять их самые длинные цепочки из одинаковых элементов");
		puts("");
		puts("0) exit program");

		while (scanf_s(" %d", &n) != 1) {
			scanf_s("%*[^\n]");
			scanf_s("%*c");
		}
		puts("");

		switch (n)
		{
		case 1:
			printf("delete index = ");
			scanf_s("%d", &id);
			deleteindex(id, arr, &size);
			break;
		case 2:
			printf("value = ");
			scanf_s("%d", &val);
			printf("index = ");
			scanf_s("%d", &id);
			insert(val, id, arr, &size);
			break;
		case 3:
			deleteindex(index(arrmin(arr, size), arr, size), arr, &size);
			break;
		case 4:
			insert(0, index(arrmin(arr, size), arr, size), arr, &size);
			break;
		case 5:
			for (int i = 0; i < size; i++) {
				if (arr[i] % 2 == 0) deleteindex(i, arr, &size);
			}
			break;
		case 6:
			for (int i = 0; i < size; i++) {
				if (arr[i] % 2 == 0) {
					insert(arr[i], i, arr, &size);
					i += 2;
				}
			}
			break;
		case 7:
			insert(arrmin(arr, size), 0, arr, &size);
			break;
		case 99:
			deletemax3(arr, &size);
			break;
		case 10:
			for (int i = 0; i < size; i++) {
				if (count(arr[i], arr, size) == 1) {
					deleteindex(index(arr[i], arr, size), arr, &size);
					i -= 1;
				}
			}
			break;
		case 11:
			exchange_max_chains(A, B, &sA, &sB);
			break;
		case 0:
			puts("goodbye :3");
			break;
		default:
			puts("error: wrong N");
			break;
		}

	} while (n != 0);
	return 0;
}
