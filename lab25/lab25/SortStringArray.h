#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../../string_my/string_my.h"


// Максимальная длина слова в массиве
#define MAX_LEN_WORD 80
// Максимальное количество слов
#define MAX_WORDS 20000

// Слова, загруженные из файла 
extern char words[MAX_WORDS][MAX_LEN_WORD];
// Количество слов в массиве
extern int n = 0;
// Массив для сортировки 
extern char a[MAX_WORDS][MAX_LEN_WORD];

int LoadWords(char* filename);
void CopyWordsToA();
int ArraysAreEqual();
int isSortedStringArray(char a[MAX_WORDS][MAX_LEN_WORD]);
void swapWords(char a[], char b[]);

void SelectionSortStrings();
void QuickSortStrings();
void BubbleSortStrings();
void InsertionSortStrings();
char* MergeSortStrings(char* up, char* down, unsigned int left, unsigned int right);
void ShellSort(char* array, int size);

int LinearSearchStrings(char target[], char source[MAX_WORDS][MAX_LEN_WORD]);
int BinarySearchStrings(char target[], char source[MAX_WORDS][MAX_LEN_WORD]);
