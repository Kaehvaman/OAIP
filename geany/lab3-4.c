#include <stdio.h>
#include <Windows.h>

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	int nums[5];
	int max;
	
	printf("введите 5 целых чисел: ");
	scanf_s("%d%d%d%d%d", &nums[0], &nums[1], &nums[2], &nums[3], &nums[4]);
	
	max = nums[0];
	
	for (int i = 1; i < 5; i++) {
		if (nums[i] > max) max = nums[i];
	}
	
	printf("max = %d", max);
	
	return 0;
}
