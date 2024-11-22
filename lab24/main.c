#include <stdio.h>
#include <ctype.h>

void task1() {
	FILE* fin = fopen("files/text1.txt", "r");
	if (fin == NULL) {
		puts("File cannot be opened");
		return 0;
	}
	FILE* fout = fopen("files/out1.html", "r");
	if (fin == NULL) {
		puts("File cannot be opened");
		return 0;
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
}


int main() {
	
	task1();

	return 0;
}
