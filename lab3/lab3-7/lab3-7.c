#include <stdio.h>
#include <Windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	int v;
	printf("�������� ������� � ��/� = ");
	scanf_s("%d", &v);
	
	if (v > 3000) puts("���������");
	else if (v > 1200) puts("����� ������");
	else if (v > 800) puts("������");
	else if (v > 500) puts("���������");
	else if (v > 200) puts("��������");
	else puts("����� ��������");
	
	return 0;
}

