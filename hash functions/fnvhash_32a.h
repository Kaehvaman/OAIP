#pragma once

/*
 * https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
 * http://www.isthe.com/chongo/tech/comp/fnv/index.html
*/

/*
 * To use the recommended 32 bit FNV-1a hash, pass FNV1_32A_INIT as the
 * Fnv32_t hashval argument to fnv_32a_buf() or fnv_32a_str().
*/

typedef uint32_t Fnv32_t;

/*
 * 32 bit magic FNV-1a prime
*/
#define FNV_32_PRIME ((Fnv32_t)0x01000193)

/*
 * 32 bit FNV-1 and FNV-1a non-zero initial basis
 *
 * The FNV-1 initial basis is the FNV-0 hash of the following 32 octets:
 *
 *              chongo <Landon Curt Noll> /\../\
 *
 * NOTE: The \'s above are not back-slashing escape characters.
 * They are literal ASCII  backslash 0x5c characters.
 *
 * NOTE: The FNV-1a initial basis is the same value as FNV-1 by definition.
 */
#define FNV1_32_INIT ((Fnv32_t)0x811c9dc5)
#define FNV1_32A_INIT FNV1_32_INIT

/*
 * If you need an x-bit hash where x is not a power of 2,
 * then we recommend that you compute the FNV hash that is just larger than x-bits
 * and xor-fold the result down to x-bits.By xor-folding we mean shift the excess 
 * high order bits down and xor them with the lower x - bits.
*/

//For example to produce a 24 bit FNV-1 hash in C we xor-fold fold a 32 bit FNV-1 hash:

#define MASK_24 (((uint32_t)1<<24)-1) /* i.e., (uint32_t)0xffffff */
/*
uint32_t hash;
void* data;
size_t data_len;

hash = fnv_32_buf(data, data_len, FNV1_32_INIT);
hash = (hash >> 24) ^ (hash & MASK_24);
*/

#define FNV_24(hash) ((hash >> 24) ^ (hash & MASK_24))

//To produce a 16 bit FNV-1 hash in C we xor-fold fold a 32 bit FNV-1 hash:

#define MASK_16 (((uint32_t)1<<16)-1) /* i.e., (uint32_t)0xffff */
/*
uint32_t hash;
void* data;
size_t data_len;

hash = fnv_32_buf(data, data_len, FNV1_32_INIT);
hash = (hash >> 16) ^ (hash & MASK_16);
*/

#define FNV_16(hash) ((hash >> 16) ^ (hash & MASK_16))

//For tiny x < 16 bit values, we recommend using a 32 bit FNV - 1 hash as follows:

/* NOTE: for 0 < x < 16 ONLY!!! */
#define TINY_MASK(x) (((uint32_t)1<<(x))-1)
/*
uint32_t hash;
void* data;
size_t data_len;

hash = fnv_32_buf(data, data_len, FNV1_32_INIT);
hash = (((hash >> x) ^ hash) & TINY_MASK(x));
*/

#define TINY_FNV(x, hash) (((hash >> x) ^ hash) & TINY_MASK(x))

Fnv32_t fnv_32a_buf(void* buf, size_t len, Fnv32_t hval);
Fnv32_t fnv_32a_str(char* str, Fnv32_t hval);
