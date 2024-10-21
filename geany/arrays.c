#include <stdio.h>

#define M 3
#define N 3

void printarr(int m, int n, int a[M][N]) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("%2d ", a[i][j]);
		}
		printf("\n");
	}
}

void intmulti(int m, int n, int a[M][N], int x) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			a[i][j] = a[i][j] * x;
		}
	}
}

void addmx(int m, int n, int A[M][N], int B[M][N], int C[M][N]) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			C[i][j] = A[i][j] + B[i][j];
		}
	}
}

void mulmx(int m, int n, int A[M][N], int B[M][N], int C[M][N]) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			for (int p = 0; p < n; p++)
				C[i][j] += + A[i][p] * B[p][j];
		}
	}
}

void transpone(int m, int n, int A[M][N], int At[M][N]) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			At[i][j] = A[j][i];
		}
	}
}

int main() {
	/*
	int A[2][2] = {{3, -2}, {5, -4}};
	int B[2][2] = {{3, 4}, {2, 5}};
	int C[2][2] = {{0, 0}, {0, 0}};
	mulmx(2, 2, A, B, C);
	printarr(2, 2, C);
	*/
	int A[M][N] = { {5, 8, -4}, {6, 9, -5}, {4, 7, -3} };
	int B[M][N] = { {3, 2, 5}, {4, -1, 3}, {9, 6, 5} };
	int C[M][N] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
	/*int D[M][N] = {
		{1, 1, 1},
		{1, 1, 1},
		{1, 1, 1},
	};*/
	printarr(M, N, A);
	puts("");
	printarr(M, N, B);
	puts("");
	mulmx(M, N, A, B, C);
	printarr(M, N, C);
	puts("");
	//printarr(M, N, D);
	//puts("");
	
	//addmx(M, N, A, B, C);
	//printarr(M, N, C);
	
	//intmulti(M, N, A, 2);
	//printarr(M, N, A);
	
	return 0;
}

/*
int A[M][N] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
int B[M][N] = { {1, 1, 1}, {1, 1, 1}, {1, 1, 1} };
int C[M][N] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };*/
