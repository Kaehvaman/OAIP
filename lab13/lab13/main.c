#include <stdio.h>
#include <Windows.h>

void arrayinput(int arr[], int len) {
	printf("������� %d ��������� �������\n", len);
	for (int i = 0; i < len; i++) {
		scanf_s(" %d", &arr[i]);
	}
}

void printarr(int arr[], int len) {
	printf("���������� �������: [");
	for (int i = 0; i < len; i++) {
		printf("%d, ", arr[i]);
	}
	printf("\b\b]\n");
}

void odds10x(int arr[], int len) {
	for (int i = 0; i < len; i++) {
		if (arr[i] % 2 != 0) arr[i] *= 10;
	}
}

void lasteven2x(int arr[], int len) {
	for (int i = len - 1; i > 0; i--) {
		if (arr[i] % 2 == 0) {
			arr[i] *= 2;
			break;
		}
	}
}

int index(int num, int arr[], int len) {
	for (int i = 0; i < len; i++) {
		if (arr[i] == num) return i;
	}
	return -1;
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

void switchmaxmin(int arr[], int len) {
	int tmpmax = arrmax(arr, len);
	int tmpmin = arrmin(arr, len);
	int maxi = index(tmpmax, arr, len);
	int mini = index(tmpmin, arr, len);
	arr[maxi] = tmpmin;
	arr[mini] = tmpmax;
}

void evenleftmin(int arr[], int len) {
	int id = index(arrmin(arr, len), arr, len);
	int count = 0;
	for (int i = 0; i < id; i++) {
		if (arr[i] % 2 == 0) count++;
	}
	printf("����� ������ ����� ������������ = %d\n", count);
}

void negeven(int arr[], int len) {
	for (int i = 0; i < len; i++) {
		if (arr[i] % 2 == 0) arr[i] *= -1;
	}
}

void replace4(int arr[], int len) {
	for (int i = 0; i < len; i++) {
		if (arr[i] < 4) arr[i] = 4;
	}
}

void replacemax0(int arr[], int len) {
	int maxi = index(arrmax(arr, len), arr, len);
	for (int i = maxi; i < len; i++) {
		if (arr[i] % 2 != 0) arr[i] = 0;
	}
}

void muleveneven(int arr[], int len) {
	int even1 = 0;
	int even2 = len - 1;
	for (int i = 0; i < len; i++) {
		if (arr[i] % 2 == 0) {
			even1 = i + 1;
			break;
		}
	}
	for (int i = len - 1; i > 0; i--) {
		if (arr[i] % 2 == 0) {
			even2 = i;
			break;
		}
	}
	for (int i = even1; i < even2; i++) {
		arr[i] *= 100;
	}
}

#define ARRNUM 10

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int arr[ARRNUM] = {5, 7, 12, 3, 4, 8, -1, 6, 1, 7};
	/*for (int i = 0; i < ARRNUM; i++) {
		arr[i] = 0;
	}*/

	int n = -1;
	do {
		puts("\n");
		printarr(arr, ARRNUM);
		puts("�������� ���������");
		puts("1) ������ ����� � ������");
		puts("2) �������� �������� ����� �� 10");
		puts("3) �������� ��������� ������ ����� �� 2");
		puts("4) ������� ������ ����� ������������");
		puts("6) �������� ���� � ��� �������");
		puts("7) ��� ������ �������� ������� �������� �� -1");
		puts("8) ��� �������� ������� ������� �������� ������ 4 �������� �� 4");
		puts("9) ��� �������� ��������, ������� ����� �������������, �������� �� 0");
		puts("11) ��� �������� ����� ������ � ��������� ������ ��������� � 100 ���");
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
			arrayinput(arr, ARRNUM);
			break;
		case 2:
			odds10x(arr, ARRNUM);
			break;
		case 3:
			lasteven2x(arr, ARRNUM);
			break;
		case 4:
			evenleftmin(arr, ARRNUM);
			break;
		case 6:
			switchmaxmin(arr, ARRNUM);
			break;
		case 7:
			negeven(arr, ARRNUM);
			break;
		case 8:
			replace4(arr, ARRNUM);
			break;
		case 9:
			replacemax0(arr, ARRNUM);
			break;
		case 11:
			muleveneven(arr, ARRNUM);
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