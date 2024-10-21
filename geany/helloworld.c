#include <stdio.h>
#include <locale.h>
#include <Windows.h>

int main() {
	printf("default cp = %d\n", GetConsoleCP());
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	printf("new cp = %d\n", GetConsoleCP());
	//printf("%s\n", setlocale(LC_ALL, "Russian_Russia.866"));
	//printf("%s\n", setlocale(LC_CTYPE, ""));
	printf("Hello world! Привет мир!\n");
	printf("%f\n", 1234567.89);
	char str[200];
	printf(" input text: ");
	fgets(str, sizeof(str), stdin);
	//scanf("%5[^\n]", str);
	printf("output text: %s", str);
	printf("lolol");
	return 0;
}

