#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define BUFLEN 128

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

void task1() {
	FILE* fin = fopen("files/text1.txt", "r");
	if (fin == NULL) {
		puts("File cannot be opened");
		return;
	}
	FILE* fout = fopen("files/out1.html", "w");
	if (fin == NULL) {
		puts("File cannot be opened");
		return;
	}

	fprintf(fout, "<!DOCTYPE html>");
	fprintf(fout, "<html>");
	fprintf(fout, "<head>");
	fprintf(fout, "<meta http - equiv = \"Content-Type\" content = 	\"text/html; charset=utf-8\" />");
	fprintf(fout, "<title>HTML Document</title>");
	fprintf(fout, "</head>");
	fprintf(fout, "<body>");

	char ch;
	while ((ch = getc(fin)) != EOF) {
		if (ch == '\n') {
			fprintf(fout, "<br>");
		}
		else {
			putc(ch, fout);
		}
	}

	fprintf(fout, "</body>");
	fprintf(fout, "</html>");

	fclose(fin);
	fclose(fout);
}

void task2() {
	FILE* fin = fopen("files/text2.txt", "r");
	if (fin == NULL) {
		puts("File cannot be opened");
		return;
	}
	FILE* fout = fopen("files/out2.html", "w");
	if (fout == NULL) {
		puts("File cannot be opened");
		return;
	}

	fprintf(fout, "<!DOCTYPE html>");
	fprintf(fout, "<html>");
	fprintf(fout, "<head>");
	fprintf(fout, "<meta http - equiv = \"Content-Type\" content = 	\"text/html; charset=utf-8\" />");
	fprintf(fout, "<title>HTML Document</title>");
	fprintf(fout, "</head>");
	fprintf(fout, "<body>");

	char buf[BUFLEN];
	char tmp[BUFLEN];
	int ch;
	while (feof(fin) == 0 && ferror(fin) == 0) {
		while (getNextDelim(fin, &ch)) {
			if (ch == '\n') {
				fprintf(fout, "<br>");
			}
			else {
				fprintf(fout, "%c", ch);
			}
		}

		if (getNextWord(fin, buf, BUFLEN)) {
			int isbold = 0;
			int isitalic = 0;

			int len = (int)strlen(buf);
			if (len >= 2 && buf[len-2] == buf[len-1]) {
				isbold = 1;
			}

			int count = 0;
			for (int i = 0; i < len; i++) {
				if (isupper(buf[i])) {
					count += 1;
				}
			}
			if (count == len) {
				isitalic = 1;
			}

			if (isbold) {
				strcpy(tmp, buf);
				sprintf(buf, "<b>%s</b>", tmp);
			}

			if (isitalic) {
				strcpy(tmp, buf);
				sprintf(buf, "<i>%s</i>", tmp);
			}

			fprintf(fout, "%s", buf);
		}
	}

	fprintf(fout, "</body>");
	fprintf(fout, "</html>");

	fclose(fin);
	fclose(fout);
}

int main() {
	
	//task1();
	task2();

	return 0;
}
