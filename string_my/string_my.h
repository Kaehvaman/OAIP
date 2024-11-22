#ifndef STRING_MY_H
#define STRING_MY_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int getNextDelim(FILE* file, int* token);
int getNextWord(FILE* file, char token[], int len);

int strlen_my_arr(char str[]);
int strlen_my_ptr(char* str_ptr);
int strcmp_my_arr(char str1[], char str2[]);
int strcmp_my_ptr(char* str1, char* str2);
char* strcpy_my_arr(char dest[], char source[]);
char* strcpy_my_ptr(char* dest, char* source);
char* strcat_my_ptr(char* destination, const char* source);
char* strchr_my_arr(char str[], int ch);
char* strchr_my_ptr(char* str, int ch);
char toupperMY(char ch);

#endif
