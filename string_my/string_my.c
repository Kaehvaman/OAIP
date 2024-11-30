#include "string_my.h"

int getNextDelim(FILE* file, int* token) {
	int ch = getc(file);
	if (ch == EOF) {
		return 0;
	}

	if (isalnum(ch)) {
		ungetc(ch, file);
		return 0;
	}

	*token = ch;
	return 1;
}

int getNextWord(FILE* file, char token[], int len) {
	int ch;
	int i = 0;
	while ((ch = getc(file)) != EOF && (i < len - 1)) {
		if (isalnum(ch)) {
			token[i] = ch;
		}
		else {
			break;
		}
		i += 1;
	}
	ungetc(ch, file);
	token[i] = '\0';
	if (i == 0) {
		return 0;
	}
	else {
		return 1;
	}
}

int strlen_my_arr(char str[]) {
	int len = 0;
	while (str[len] != '\0') {
		len++;
	}
	return len;
}

int strlen_my_ptr(char* str_ptr) {
	char* str_ptr_old = str_ptr;
	while (*str_ptr != '\0') {
		str_ptr++;
	}
	return (int)(str_ptr - str_ptr_old);
}

int strcmp_my_arr(char str1[], char str2[]) {
	int i = 0;
	while (str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i]) {
		i++;
	}
	return str1[i] - str2[i];
}

int strcmp_my_ptr(char* str1, char* str2) {
	while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2) {
		str1++;
		str2++;
	}
	return *str1 - *str2;
}

char* strcpy_my_arr(char dest[], char source[]) {
	int i = 0;
	while (source[i] != '\0') {
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
	return dest;
}

char* strcpy_my_ptr(char* dest, char* source) {
	while (*source != '\0') {
		*dest = *source;
		dest++;
		source++;
	}
	*dest = '\0';
	return dest;
}

char* strcat_my_ptr(char* destination, const char* source) {
	while (*destination != '\0') {
		destination++;
	}
	while (*source != '\0') {
		*destination = *source;
		destination++;
		source++;
	}
	return destination;
}

char* strchr_my_arr(char str[], int ch) {
	int i = 0;
	while (str[i] != '\0') {
		if (str[i] == (char)ch) {
			return &str[i];
		}
		i++;
	}
	return NULL;
}

char* strchr_my_ptr(char* str, int ch) {
	while (*str != '\0') {
		if (*str == (char)ch) {
			return str;
		}
		str++;
	}
	return NULL;
}

char toupperMY(char ch) {
	if (ch >= 'a' && ch <= 'z') {
		return 'A' + (ch - 'a');
	}
	if (ch >= 'à' && ch <= 'ÿ') {
		return 'À' + (ch - 'à');
	}
	if (ch == '¸') {
		return '¨';
	}
	return ch;
}
