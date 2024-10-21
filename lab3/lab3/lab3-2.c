#include <stdio.h>
#include <Windows.h>

int main() {
	int max, v1, v2, v3;
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	printf("введите 3 целых числа: ");
	scanf_s("%d%d%d", &v1, &v2, &v3);
	max = v1;
	
	if (v2 > max) {
		max = v2;
	}
	
	if (v3 > max) {
		max = v3;
	}
	
	printf("max = %d", max);
	
	return 0;
}

