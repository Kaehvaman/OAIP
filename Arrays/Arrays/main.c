#include <stdio.h>

#define M 3
#define N 3

int main() {
	int arr[M][N] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d", arr[i][j]);
		}
		printf("\n");
	}
	hello();
	return 0;
}