#include <stdio.h>
#include <Windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	int v;
	printf("скорость самолёта в км/ч = ");
	scanf_s("%d", &v);
	
	if (v > 3000) puts("мгновенно");
	else if (v > 1200) puts("очень быстро");
	else if (v > 800) puts("быстро");
	else if (v > 500) puts("нормально");
	else if (v > 200) puts("медленно");
	else puts("очень медленно");
	
	return 0;
}

