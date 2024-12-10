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
    char s1[] = "ddggdd";
    char s2[] = "cddc";
    unsigned int h1 = fnv_32a_str(s1, FNV1_32A_INIT);
    unsigned int h2 = fnv_32a_str(s2, FNV1_32A_INIT);
    unsigned int h11, h12, h13;
   
    printBits(4, &h1);
    h11 = FNV_16(h1);
    h12 = TINY_FNV(15, h1);
    h13 = (h1 & hashmask(16));
    printBits(4, &h11);
    printBits(4, &h12);
    printBits(2, &h13);

    return 0;
}