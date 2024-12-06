#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#include "Dict.h"

int getNextDelim(FILE* fp, char token[]);
int getNextWord(FILE* fp, char token[], int maxLen);

int LoadDictionary(char* filename);
int TextProcessing(char* filenameIn, char* filenameOut);

char filenameDict[MAX_PATH] = "../Dictionaries/dict0.txt";
char filenameIn[MAX_PATH] = "../Texts/Alice.txt";
char filenameOut[MAX_PATH] = "out/Alice_out.html";

double results[3][12];

void test(int i, int j) {
	// �������� ����� ����� ��������������
	printf("HTML = %s\ntext = %s\ndict = %s\n",
		filenameOut, filenameIn, filenameDict);

	LoadDictionary(filenameDict);

	clock_t t0 = clock();
	TextProcessing(filenameIn, filenameOut);
	clock_t t1 = clock();

	Destroy();
	
	double runtime = (t1 - t0) / (double)CLOCKS_PER_SEC;
	results[i][j] = runtime;
	printf("t1 - t0 = %.3f sec (Run time of HTML generating)\n\n", runtime);
}

void test_dicts(int i) {
	for (int j = 0; j < 4; j++) {
		sprintf(filenameDict, "../Dictionaries/dict%d.txt", j);
		test(i, j);
		sprintf(filenameDict, "../Dictionaries/dict%da.txt", j);
		test(i, j+4);
		sprintf(filenameDict, "../Dictionaries/dict%db.txt", j);
		test(i, j+8);
	}
}

int main() {
	strcpy(filenameIn, "../Texts/Alice.txt");
	strcpy(filenameOut, "out/Alice_out.html");
	test_dicts(0);
	strcpy(filenameIn, "../Texts/Tolkien.txt");
	strcpy(filenameOut, "out/Tolkien_out.html");
	test_dicts(1);
	strcpy(filenameIn, "../Texts/Tolkien2.txt");
	strcpy(filenameOut, "out/Tolkien2_out.html");
	test_dicts(2);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 12; j++) {
			printf("%7.3lf ", results[i][j]);
		}
		printf("\n");
	}

	printf("\a");
	
	return 0;
}

int LoadDictionary(char* filename) {
	// ������� ����
	FILE* fin = fopen(filename, "r");
	if (fin == NULL) {
		// ���� ���� �� ������ ������� - �������� �� ����
		printf("File %s didn't open!\n", filename);
		return 0;
	}

	Create();
	char token[MAX_LEN_WORD];

	// ���� �� ����� �����
	while (!feof(fin)) {
		// ���� ���� ����������� - ����� ���
		while (getNextDelim(fin, token)) {
		}
		// ���� ���� ����� - ����� ���
		if (getNextWord(fin, token, MAX_LEN_WORD)) {
			Insert(token);
		}
	}
	// ��������� ���� � �������
	fclose(fin);
	return 1;
}

int TextProcessing(char* filenameIn, char* filenameOut) {
	// ������� ���� �������
	FILE* fin = fopen(filenameIn, "r");
	if (fin == NULL) {
		// ���� ���� �� ������ ������� - �������� �� ����
		printf("File %s doesn't opened!\n", filenameIn);
		return 0;
	}

	// ������� ���� ��������
	FILE* fout = fopen(filenameOut, "w");
	if (fout == NULL) {
		// ���� ���� �� ������ ������� - �������� �� ����
		printf("File %s doesn't opened!\n", filenameOut);
		// � ��������� ������� ����
		fclose(fin);
		return 0;
	}

	// ������� � �������� ���� ��������� HTML ���������
	fprintf(fout, "<!DOCTYPE html>");
	fprintf(fout, "<html>");
	fprintf(fout, "<head>");
	fprintf(fout, "<meta http-equiv = \"Content-Type\" content = \"text/html; charset=cp1251\" />");
	fprintf(fout, "<title>HTML Document</title>");
	fprintf(fout, "</head>");
	fprintf(fout, "<body>");
	char token[MAX_LEN_WORD];

	// ���� �� ����� �����
	while (!feof(fin)) {
		// ���� ���� ����������� - ����� ���
		while (getNextDelim(fin, token)) {
			// ������� ����������� 
			if (strcmp(token, "<") == 0) {
				fprintf(fout, "&lt");
			}
			else 	if (strcmp(token, ">") == 0) {
				fprintf(fout, "&gt");
			}
			else {
				if (strcmp(token, "\n") == 0) {
					fprintf(fout, "<br>");
				}
				fprintf(fout, "%s", token);
			}
		}
		// ���� ���� ����� - ����� ���
		if (getNextWord(fin, token, MAX_LEN_WORD)) {
			// ���� ����� ���� � ������� � �� �������� ���
			if (Member(token)) {
				fprintf(fout, "<b>%s</b>", token);
			}
			else {
				fprintf(fout, "%s", token);
			}
		}
	}

	// ������� � HTML ����������� ���� ��������� HTML
	fprintf(fout, "</body>");
	fprintf(fout, "</html>");
	// ��������� ������� � �������� �����
	fclose(fin);
	fclose(fout);

	return 1;
}

int isalpha_my(unsigned char ch);

// ���������� 1 - ����  �� ����� �������� �����������.
// � ���� ������ � token ������������ ������, ���������� 
// ���� �����������.
// ���� � ����� ��� �� ����������� - ���������� 0.
// � ���� ������ ��������� token ������������.
int getNextDelim(FILE* fp, char token[])
{
	int ch = getc(fp);
	if (ch == EOF) {
		return 0;
	}
	if (isalpha_my((unsigned char)ch)) {
		ungetc(ch, fp);
		return 0;
	}
	token[0] = (unsigned char)ch;
	token[1] = '\0';
	return 1;
}


// ���������� 1 - ����  �� ����� ��������� �����.
// � ���� ������ � token ������������ ������, ���������� 
// ��� �����. ������������� ��� ����� �� ������ maxLen ��������.
// ���� � ����� �� ���� ����� - ���������� 0.
// � ���� ������ token �������� ������ ������.
int getNextWord(FILE* fp, char token[], int maxLen)
{
	int i = 0;
	int ch;
	while (((ch = getc(fp)) != EOF) && (i < maxLen - 1)) {
		if (!isalpha_my((unsigned char)(ch))) {
			break;
		}
		token[i++] = ch;
	}
	ungetc(ch, fp);
	token[i] = '\0';
	if (i == 0)
		return 0;
	return 1;
}


// ���������� 0 - ���� ch - �� �����.
// ���������� 1 - ���� ch - �����.
// ��������� �������� ��� ��������� ���� (� ������ < 128)
// � ��� ������� ���� �� ��������� ANSI
int isalpha_my(unsigned char ch) {
	if (isalpha(ch))
		return 1;

	// ANSI ���������!!!
	if (ch >= 192 && ch <= 223)
		return 1;
	if (ch >= 224 && ch <= 255)
		return 1;

	/*
		if (ch >= '�' && ch <= '�') return 1;
		if (ch >= '�' && ch <= '�') return 1;
		if (ch >= '�' && ch <= '�')return 1;
		if (ch == '�' ) return 1;
		if (ch == '�') return 1;*/

	return 0;
}
