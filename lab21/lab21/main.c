#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <Windows.h>

void task1() {
	printf("task1 Введите символ: ");
	char ch;
	scanf_s(" %c", &ch, 1);
	for (int i = ch; i <= ch + 19; i++) {
		printf("'%c' (%#x)(%d)\n", i, i, i);
	}
	printf("\n\n");
}

void task2() {
	printf("task2 Введите символ: ");
	char ch;
	scanf_s(" %c", &ch, 1);
	for (int i = ch; i >= ch - 29; i--) {
		printf("'%c' (%#x)(%d)\n", i, i, i);
	}
	printf("\n\n");
}

void task3() {
	char str[81];
	printf("task3 Введите строку: ");
	fgets(str, 81, stdin);
	printf("Вы ввели строку: \"%s\"\n", str);

	int count = 0;
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == ' ') count++;
	}
	printf("В ней %d пробелов", count);
}

void task4() {
	char str[81];
	printf("task4 Введите строку: ");
	fgets(str, 81, stdin);
	printf("Вы ввели строку: \"%s\"\n", str);

	int count = 0;
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == ' ') str[i] = '#';
	}
	printf("Строка после обработки: \"%s\"\n", str);
}

void task5_1() {
	char str[81];
	printf("task5_1 Введите строку: ");
	fgets(str, 81, stdin);
	printf("Вы ввели строку: \"%s\"\n", str);

	int count = 0;
	for (int i = 0; i < strlen(str); i++) {
		if (isdigit(str[i])) str[i] = '$';
	}
	printf("Строка после обработки: \"%s\"\n", str);
}

char isdigitMY(char ch) {
	if (ch >= '0' && ch <= '9') {
		return 1;
	}
	else {
		return 0;
	}
}

void task5_2() {
	char str[81];
	printf("task5_2 Введите строку: ");
	fgets(str, 81, stdin);
	printf("Вы ввели строку: \"%s\"\n", str);

	int count = 0;
	for (int i = 0; i < strlen(str); i++) {
		if (isdigitMY(str[i])) str[i] = '$';
	}
	printf("Строка после обработки: \"%s\"\n", str);
}

void task6_1() {
	char str[81];
	printf("task6_1 Введите строку: ");
	fgets(str, 81, stdin);
	printf("Вы ввели строку: \"%s\"\n", str);
	
	for (int i = 0; i < strlen(str); i++) {
		str[i] = toupper(str[i]);
	}

	printf("Строка после обработки: \"%s\"\n", str);
}

char toupperMY(char ch) {
	if (ch >= 'a' && ch <= 'z') {
		return 'A' + (ch - 'a');
	}
	if (ch >= 'а' && ch <= 'я') {
		return 'А' + (ch - 'а');
	}
	if (ch == 'ё') {
		return 'Ё';
	}
	return ch;
}

void task6_2() {
	char str[81];
	printf("task6_2 Введите строку: ");
	fgets(str, 81, stdin);
	printf("Вы ввели строку: \"%s\"\n", str);

	for (int i = 0; i < strlen(str); i++) {
		str[i] = toupperMY(str[i]);
	}

	printf("Строка после обработки: \"%s\"\n", str);
}

void task9_9() {
	char str[81];
	printf("task9_9 Введите строку: ");
	fgets(str, 81, stdin);
	printf("Вы ввели строку: \"%s\"\n", str);

	for (int i = 0; i < strlen(str); i++) {
		if (
			str[i] == '!' || str[i] == '?' || str[i] == '.' || 
			str[i] == ',' || str[i] == ':' || str[i] == ';' ||
			str[i] == '\"' || str[i] == '\''
			) { str[i] = '_'; }
	}

	printf("Строка после обработки: \"%s\"\n", str);
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_CTYPE, "");

	//task1();
	//task2();
	//task3();
	//task4();
	//task5_1();
	//task5_2();
	//task6_1();
	//task6_2();
	//task9_9();

	return 0;
}