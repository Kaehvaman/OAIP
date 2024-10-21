#include <stdio.h>
#include <Windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	int n;
	printf("n = ");
	scanf_s("%d", &n);
	
	int i = 1;
	do {
		printf("%d ", i);
		i += 1;
	} while (i <= n);
	
	return 0;
}

