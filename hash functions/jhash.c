#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "jhash.h"

/*
from https://www.burtleburtle.net/bob/c/lookup2.c
--------------------------------------------------------------------
jhash() -- hash a variable-length key into a 32-bit value
  k     : the key (the unaligned variable-length array of bytes)
  len   : the length of the key, counting by bytes
  initval : the previous hash, or an arbitrary value
Returns a 32-bit value.  Every bit of the key affects every bit of
the return value.  Every 1-bit and 2-bit delta achieves avalanche.
About 36+6len instructions.

The best hash table sizes are powers of 2.  There is no need to do
mod a prime (mod is sooo slow!).  If you need less than 32 bits,
use a bitmask.  For example, if you need only 10 bits, do
  h = (h & hashmask(10));
In which case, the hash table should have hashsize(10) elements.

If you are hashing n strings (ub1 **)k, do it like this:
  for (i=0, h=0; i<n; ++i) h = hash( k[i], len[i], h);

By Bob Jenkins, 1996.  bob_jenkins@burtleburtle.net.  You may use this
code any way you wish, private, educational, or commercial.  It's free.

See http://burtleburtle.net/bob/hash/evahash.html
Use for hash table lookup, or anything where one collision in 2^32 is
acceptable.  Do NOT use for cryptographic purposes.
--------------------------------------------------------------------
*/

ub4 jhash(register ub1* k, register ub4  length, register ub4  initval)
{
    register ub4 a, b, c, len;

    /* Set up the internal state */
    len = length;
    a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
    c = initval;           /* the previous hash value */

    /*---------------------------------------- handle most of the key */
    while (len >= 12)
    {
        a += (k[0] + ((ub4)k[1] << 8) + ((ub4)k[2] << 16) + ((ub4)k[3] << 24));
        b += (k[4] + ((ub4)k[5] << 8) + ((ub4)k[6] << 16) + ((ub4)k[7] << 24));
        c += (k[8] + ((ub4)k[9] << 8) + ((ub4)k[10] << 16) + ((ub4)k[11] << 24));
        mix(a, b, c);
        k += 12; len -= 12;
    }

    /*------------------------------------- handle the last 11 bytes */
    c += length;
    switch (len)              /* all the case statements fall through */
    {
    case 11: c += ((ub4)k[10] << 24);
    case 10: c += ((ub4)k[9] << 16);
    case 9: c += ((ub4)k[8] << 8);
        /* the first byte of c is reserved for the length */
    case 8: b += ((ub4)k[7] << 24);
    case 7: b += ((ub4)k[6] << 16);
    case 6: b += ((ub4)k[5] << 8);
    case 5: b += k[4];
    case 4: a += ((ub4)k[3] << 24);
    case 3: a += ((ub4)k[2] << 16);
    case 2: a += ((ub4)k[1] << 8);
    case 1: a += k[0];
        /* case 0: nothing left to add */
    }
    mix(a, b, c);
    /*-------------------------------------------- report the result */
    return c;
}