#include <stdio.h>


void printarr(int arr[], int len) {
	printf("[");
	for (int i = 0; i < len; i++) {
		printf("%d, ", arr[i]);
	}
	printf("\b\b]");
}

int main() {

	int a[20];
	int b[-1];

	printarr(a, 20);
	printf("\n");
	printarr(b, 5);

	return 0;
}