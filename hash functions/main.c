#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#include "jhash.h"
#include "fnvhash_32a.h"

// Assumes little endian
void printBits(size_t const size, void const* const ptr) {
    unsigned char* b = (unsigned char*)ptr;
    unsigned char byte;
    int i, j;

    for (i = (int)size - 1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

int main() {
    char s1[] = "cbbc";
    char s2[] = "cddc";
    Fnv32_t h1 = fnv_32a_str(s1, FNV1_32A_INIT);
    Fnv32_t h2 = fnv_32a_str(s2, FNV1_32A_INIT);
    Fnv32_t h11 = h1;
   

    printBits(4, &h1);
    h1 = FNV_16(h1);
    h11 = TINY_FNV(15, h1);
    printBits(4, &h1);
    printBits(4, &h11);

    return 0;
}