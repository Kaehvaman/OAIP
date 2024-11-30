#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../../string_my/string_my.h"


// ������������ ����� ����� � �������
#define MAX_LEN_WORD 80
// ������������ ���������� ����
#define MAX_WORDS 20000

extern int n;
// �����, ����������� �� ����� 
extern char words[MAX_WORDS][MAX_LEN_WORD];
// ������ ��� ���������� 
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
void MergeSortStrings(char arr[MAX_WORDS][MAX_LEN_WORD], int l, int r);
void ShellSort();

int LinearSearchStrings(char target[], char source[MAX_WORDS][MAX_LEN_WORD]);
int BinarySearchStrings(char target[], char source[MAX_WORDS][MAX_LEN_WORD]);
