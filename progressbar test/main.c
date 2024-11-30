#include <stdio.h>
#include <Windows.h>
#include "progressbar.h"


int main() {

	struct progressbar pg;

	progressbar_start(&pg, 100);

	for (int i = 0; i < 100; i++) {
		Sleep(100);
		progressbar_inc(&pg);
	}


	return 0;
}
