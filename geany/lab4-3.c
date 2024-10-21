#include <stdio.h>
#include <Windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	int sum, year;
	float percent;
	printf("sum = ");
	scanf("%d", &sum);
	printf("percent = ");
	scanf("%f", &percent);
	
	year = 0;
	do {
		printf("%d RUB in %d year\n", sum, year);
		sum = (sum * (100 + percent)) / 100;
		year += 1;
	} while (year <= 10);
	
	return 0;
}
