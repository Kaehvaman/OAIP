#include <stdio.h>

int x = 222;

void foo(int func()) {
	printf("%d\n", func());
}

int bar() {
	return 12345;
}

int bq() {
	return x;
}

int main() {

	foo(bar);
	foo(bq);

	return 0;
}