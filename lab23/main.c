#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>

#define BUF_LEN 128

void task1() {
	puts("===== task1 =====");

	char infilepath[] = "files/text1.txt";
	FILE* fin = fopen(infilepath, "r");
	if (fin == NULL) {
		printf("Cannot open file %s\n", infilepath);
		return;
	}

	char outfilepath[] = "files/out1.txt";
	FILE* fout = fopen(outfilepath, "w");
	if (fin == NULL) {
		printf("Cannot open file %s\n", outfilepath);
		return;
	}

	char buf[BUF_LEN];
	while (fgets(buf, BUF_LEN, fin) != NULL) {
		for (int i = 0; buf[i] != '\0'; i++) {
			if (buf[i] == '\t') {
				buf[i] = '%';
			}
		}
		fprintf(fout, "%s", buf);
		printf(">>%s<<", buf);
	}
	fclose(fin);
	fclose(fout);
}

void task2() {
	puts("===== task2 =====");

	char infilepath[] = "files/text2.txt";
	FILE* fin = fopen(infilepath, "r");
	if (fin == NULL) {
		printf("Cannot open file %s\n", infilepath);
		return;
	}

	char outfilepath[] = "files/out2.txt";
	FILE* fout = fopen(outfilepath, "w");
	if (fin == NULL) {
		printf("Cannot open file %s\n", outfilepath);
		return;
	}

	char buf[BUF_LEN];
	while (fgets(buf, BUF_LEN, fin) != NULL) {
		for (int i = 0; buf[i] != '\0'; i++) {
			buf[i] = toupper(buf[i]);
		}
		fprintf(fout, "%s", buf);
		printf(">>%s<<", buf);
	}
	fclose(fin);
	fclose(fout);
}

void task3() {
	puts("===== task3 =====");

	char infilepath[] = "files/text3.txt";
	FILE* fin = fopen(infilepath, "r");
	if (fin == NULL) {
		printf("Cannot open file %s\n", infilepath);
		return;
	}

	char outfilepath[] = "files/out3.txt";
	FILE* fout = fopen(outfilepath, "w");
	if (fin == NULL) {
		printf("Cannot open file %s\n", outfilepath);
		return;
	}

	char buf[BUF_LEN];
	while (fgets(buf, BUF_LEN, fin) != NULL) {
		for (int i = 0; buf[i] != '\0'; i++) {
			if (isalpha(buf[i])) {
				fputc('#', fout);
				break;
			}
		}
		fprintf(fout, "%s", buf);
		printf(">>%s<<", buf);
	}
	fclose(fin);
	fclose(fout);
}

void task4() {
	puts("===== task4 =====");

	char infilepath[] = "files/text4.txt";
	FILE* fin = fopen(infilepath, "r");
	if (fin == NULL) {
		printf("Cannot open file %s\n", infilepath);
		return;
	}

	char outfilepath[] = "files/out4.txt";
	FILE* fout = fopen(outfilepath, "w");
	if (fin == NULL) {
		printf("Cannot open file %s\n", outfilepath);
		return;
	}

	char buf[BUF_LEN];
	while (fgets(buf, BUF_LEN, fin) != NULL) {
		for (int i = 0; buf[i] != '\0'; i++) {
			if (ispunct(buf[i])) buf[i] = '_';
		}
		fprintf(fout, "%s", buf);
		printf(">>%s<<", buf);
	}
	fclose(fin);
	fclose(fout);
}

void task5() {
	puts("===== task5 =====");

	char infilepath[] = "files/text5.txt";
	FILE* fin = fopen(infilepath, "r");
	if (fin == NULL) {
		printf("Cannot open file %s\n", infilepath);
		return;
	}

	char outfilepath[] = "files/out5.txt";
	FILE* fout = fopen(outfilepath, "w");
	if (fin == NULL) {
		printf("Cannot open file %s\n", outfilepath);
		return;
	}

	char buf[BUF_LEN];
	while (fgets(buf, BUF_LEN, fin) != NULL) {
		int count = 0;
		for (int i = 0; buf[i] != '\0'; i++) {
			if (buf[i] == ';') {
				count += 1;
			}
		}
		fprintf(fout, "%d:%s", count, buf);
		printf(">>%d:%s<<", count, buf);
	}
	fclose(fin);
	fclose(fout);
}

int main() {

	setlocale(LC_CTYPE, "");

	task1();
	task2();
	task3();
	task4();
	task5();

	return 0;
}
