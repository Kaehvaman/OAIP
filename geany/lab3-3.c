#include <stdio.h>
#include <Windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	int t;
	printf("����������� = ");
	scanf_s("%d", &t);
	
	if (t < 18) printf("�������");
	else if (t < 22) printf("���������");
	else if (t < 26) printf("�����");
	else printf("�����");
	
	return 0;
}

