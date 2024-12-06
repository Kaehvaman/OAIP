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
	// сообщаем какие файлы обрабатываются
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
	// открыть файл
	FILE* fin = fopen(filename, "r");
	if (fin == NULL) {
		// если файл не смогли открыть - сообщаем об этом
		printf("File %s didn't open!\n", filename);
		return 0;
	}

	Create();
	char token[MAX_LEN_WORD];

	// пока не конец файла
	while (!feof(fin)) {
		// пока есть разделитель - берем его
		while (getNextDelim(fin, token)) {
		}
		// если есть слово - берем его
		if (getNextWord(fin, token, MAX_LEN_WORD)) {
			Insert(token);
		}
	}
	// Закрываем файл с текстом
	fclose(fin);
	return 1;
}

int TextProcessing(char* filenameIn, char* filenameOut) {
	// открыть файл входной
	FILE* fin = fopen(filenameIn, "r");
	if (fin == NULL) {
		// если файл не смогли открыть - сообщаем об этом
		printf("File %s doesn't opened!\n", filenameIn);
		return 0;
	}

	// открыть файл выходной
	FILE* fout = fopen(filenameOut, "w");
	if (fout == NULL) {
		// если файл не смогли открыть - сообщаем об этом
		printf("File %s doesn't opened!\n", filenameOut);
		// и закрываем входной файл
		fclose(fin);
		return 0;
	}

	// Выводим в выходной файл заголовок HTML документа
	fprintf(fout, "<!DOCTYPE html>");
	fprintf(fout, "<html>");
	fprintf(fout, "<head>");
	fprintf(fout, "<meta http-equiv = \"Content-Type\" content = \"text/html; charset=cp1251\" />");
	fprintf(fout, "<title>HTML Document</title>");
	fprintf(fout, "</head>");
	fprintf(fout, "<body>");
	char token[MAX_LEN_WORD];

	// пока не конец файла
	while (!feof(fin)) {
		// пока есть разделитель - берем его
		while (getNextDelim(fin, token)) {
			// выводим разделитель 
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
		// если есть слово - берем его
		if (getNextWord(fin, token, MAX_LEN_WORD)) {
			// Если слово есть в Словаре – то выделяем его
			if (Member(token)) {
				fprintf(fout, "<b>%s</b>", token);
			}
			else {
				fprintf(fout, "%s", token);
			}
		}
	}

	// выводит в HTML завершающие теги документа HTML
	fprintf(fout, "</body>");
	fprintf(fout, "</html>");
	// закрываем входной и выходной файла
	fclose(fin);
	fclose(fout);

	return 1;
}

int isalpha_my(unsigned char ch);

// Возвращает 1 - если  из файла прочитан разделитель.
// В этом случае в token возвращается строка, содержащая 
// этот разделитель.
// Если в файле был не разделитель - возвращает 0.
// В этом случае состояние token неопределено.
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


// Возвращает 1 - если  из файла прочитано слово.
// В этом случае в token возвращается строка, содержащая 
// это слово. Гарантируется что слово не болеее maxLen символов.
// Если в файле не было буквы - возвращает 0.
// В этом случае token содержит пустую строку.
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


// Возвращает 0 - если ch - не буква.
// Возвращает 1 - если ch - буква.
// Корректно работает для латинских букв (с кодами < 128)
// И для русских букв из кодировки ANSI
int isalpha_my(unsigned char ch) {
	if (isalpha(ch))
		return 1;

	// ANSI кодировка!!!
	if (ch >= 192 && ch <= 223)
		return 1;
	if (ch >= 224 && ch <= 255)
		return 1;

	/*
		if (ch >= 'А' && ch <= 'Я') return 1;
		if (ch >= 'а' && ch <= 'п') return 1;
		if (ch >= 'р' && ch <= 'я')return 1;
		if (ch == 'ё' ) return 1;
		if (ch == 'Ё') return 1;*/

	return 0;
}
