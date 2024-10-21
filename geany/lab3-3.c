#include <stdio.h>
#include <Windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	int t;
	printf("температура = ");
	scanf_s("%d", &t);
	
	if (t < 18) printf("холодно");
	else if (t < 22) printf("прохладно");
	else if (t < 26) printf("тепло");
	else printf("жарко");
	
	return 0;
}

