#include <stdio.h>
#include <stdlib.h>

void load(int arr[]) {
	FILE* file = fopen("\\data.txt", "r");
	if (file == NULL) {
		puts("Файл не найден");
		return;
	}

	int len;
	fscanf_s(file, "%d", &len);
	for (int i = 0; i < len; i++) {
		fscanf_s(file, "%d", &arr[i]);
	}
}

int main() {

	return 0;
}