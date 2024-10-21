#include <stdio.h>


void printTable() {
	int i = 1;
	while (i <= 9) {
		int j = 1;
		while (j <= 9) {
			printf("%d%d ", i, j);
			j++;
		}
		i++;
		puts("");
	}
}

void pithagoreanTable() {
	int i = 1;
	while (i <= 10) {
		int j = 1;
		while (j <= 10) {
			printf("%3d ", i * j);
			j++;
		}
		i++;
		puts("");
	}
}

void numTriagle() {
	int n = 0;
	printf("N = ");
	scanf_s("%d", &n);
	int i = 0;
	while (i < n) {
		int j = i;
		while (j >= 0) {
			printf("%d ", n - j);
			j--;
		}
		puts("");
		i++;
	}

}

void hardNumTriagle() {
	int n = 0;
	printf("N = ");
	scanf_s("%d", &n);
	int i = 0;
	while (i < n) {
		int space = n - i - 1;
		while (space > 0) {
			printf("   ");
			space--;
		}
		int j = i;
		while (j >= 0) {
			printf("%2d ", n - j);
			j--;
		}
		puts("");
		i++;
	}
	i--;
	while (i > 0) {
		int space = 0;
		while (space < n - i) {
			printf("   ");
			space++;
		}
		int j = i - 1;
		while (j >= 0) {
			printf("%2d ", n - j);
			j--;
		}
		puts("");
		i--;
	}

}

int main() {
	int n = -1;
	int r = 0;
	do {
		puts("\n");
		puts("choose program");
		puts("1) print ij matrix");
		puts("2) print pithagorean table");
		puts("3) print number triangle");
		puts("4) print hard number triangle");
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
			printTable();
			break;
		case 2:
			pithagoreanTable();
			break;
		case 3:
			numTriagle();
			break;
		case 4:
			hardNumTriagle();
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