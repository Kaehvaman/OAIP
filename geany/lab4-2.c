#include <stdio.h>
#include <Windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	int n;
	printf("n = ");
	scanf("%d", &n);
	
	int i = 1;
	int step = 0;
	do {
		printf("2^%d = %d\n", step, i);
		i = i * 2;
		step += 1;
	} while (step <= n);
	
	return 0;
}
