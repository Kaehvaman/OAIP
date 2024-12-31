#include <stdio.h>
#include "parallel_for.h"

int mult2(int x) {
	return x * 2;
}

static void* mult2_parallel(void* arg)
{
    int* pa = (int*) arg;
    int* result = malloc(sizeof(*result));
    *result = mult2(*pa);
    return result;
}

int main() {
    int nums[4] = { 1, 2, 3, 4 };
    void* input[4];
    void* output[4];

    input[0] = &nums[0];
    input[1] = &nums[1];
    input[2] = &nums[2];
    input[3] = &nums[3];

    forp(input, output, 4, mult2_parallel);

    for (int i = 0; i < 4; i++) {
        printf("%d\n", *(int*)output[i]);
    }

	return 0;
}