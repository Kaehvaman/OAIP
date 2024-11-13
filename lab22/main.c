#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <Windows.h>

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

char* strchr_my_arr(const char str[], int ch) {
	int i = 0;
	while (str[i] != '\0') {
		if (str[i] == (char)ch) {
			return &str[i];
		}
		i++;
	}
	return NULL;
}

char* strchr_my_ptr(const char* str, int ch) {
	while (*str != '\0') {
		if (*str == (char)ch) {
			return str;
		}
		str++;
	}
	return NULL;
}

int main() {
	char test1[] = "1234567";
	char test2[] = "12345699";
	printf("test1 string = \"%s\"\n", test1);
	printf("test2 string = \"%s\"\n", test2);
	printf("       strlen = %d\n", (int)strlen(test1));
	printf("strlen_my_arr = %d\n", strlen_my_arr(test1));
	printf("strlen_my_ptr = %d\n\n", strlen_my_ptr(test1));
	
	printf("       strcmp = %d\n", strcmp(test1, test2));
	printf("strcmp_my_arr = %d\n", strcmp_my_arr(test1, test2));
	printf("strcmp_my_ptr = %d\n\n", strcmp_my_ptr(test1, test2));

	char test_strcpy[81];
	char test_strcpy_my_arr[81];
	char test_strcpy_my_ptr[81];
	strcpy(test_strcpy, test2);
	strcpy_my_arr(test_strcpy_my_arr, test2);
	strcpy_my_ptr(test_strcpy_my_ptr, test2);
	printf("       strcopy result = \"%s\"\n", test_strcpy);
	printf("strcopy_my_arr result = \"%s\"\n", test_strcpy_my_arr);
	printf("strcopy_my_ptr result = \"%s\"\n", test_strcpy_my_ptr);

	char test_strcat[81] = "abcde";
	char test_strcat_my_ptr[81] = "abcde";
	strcat(test_strcat, test2);
	strcat_my_ptr(test_strcat_my_ptr, test2);
	printf("       strcat result = \"%s\"\n", test_strcat);
	printf("strcat_my_ptr result = \"%s\"\n\n", test_strcat_my_ptr);

	char test3[] = "qazwsxedccdexswzaq";
	printf("test3 string = \"%s\"\n", test3);

	char* strchr_res = strchr(test3, 's');
	printf("           strchr 's' = {%p} = '%c', index = %d\n", strchr_res, *strchr_res, (int)(strchr_res - test3));
	char* strchr_my_arr_res = strchr_my_arr(test3, 's');
	printf("strchr_my_arr_res 's' = {%p} = '%c', index = %d\n", strchr_my_arr_res, *strchr_my_arr_res, (int)(strchr_my_arr_res - test3));
	char* strchr_my_arr_ptr = strchr_my_ptr(test3, 's');
	printf("strchr_my_arr_ptr 's' = {%p} = '%c', index = %d\n", strchr_my_arr_ptr, *strchr_my_arr_ptr, (int)(strchr_my_arr_ptr - test3));

	return 0;
}