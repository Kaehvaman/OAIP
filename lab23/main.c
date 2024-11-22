#include <stdio.h>
#define BUF_LEN 128

void task1() {
	char filepath[] = "files/text1.txt";
	FILE* fin = fopen(filepath, "r");
	if (fin == NULL) {
		printf("Cannot open file %s\n", filepath);
		return;
	}

	char buf[BUF_LEN];
	while (fgets(buf, BUF_LEN, fin) != NULL) {

	}

}

int main() {

	



	return 0;
}
