#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <Windows.h>
#include "../string_my/string_my.h"

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
	char dest[10];

	return 0;
}