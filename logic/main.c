#include <stdio.h>
#include <iso646.h>

int f(int A, int B) {
    return (A and B) == (((not B) <= (not A)) xor A);
}

int main() {
    printf_s("A B f\n");
    for (int A = 0; A <= 1; A++) {
        for (int B = 0; B <= 1; B++) {
            printf_s("%d %d %d\n", A, B, f(A, B));
        }
    }
    return 0;
}
