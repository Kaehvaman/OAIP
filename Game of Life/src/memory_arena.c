#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "memory_arena.h"

static bool is_power_of_two(uintptr_t  x) {
	return (x & (x - 1)) == 0;
}

static uintptr_t AlignForward(uintptr_t ptr, size_t alignment) {
	uintptr_t p, a, modulo;

	assert(is_power_of_two(alignment));

	p = ptr;
	a = (uintptr_t)alignment;
	// Same as (p % a) but faster as 'a' is a power of two
	modulo = p & (a - 1);

	if (modulo != 0) {
		// If 'p' address is not aligned, push the address to the
		// next value which is aligned
		p += a - modulo;
	}
	return p;
}

void* ArenaAllocAligned(Arena* arena, size_t size, size_t alignment)
{
	uintptr_t aligned_offset_ptr = AlignForward(arena->offset_ptr, alignment);
	uintptr_t next_offset_ptr = aligned_offset_ptr + size;

	if (next_offset_ptr - (uintptr_t)arena->buffer <= arena->size)
	{
		arena->offset_ptr = next_offset_ptr;
		return (void*)aligned_offset_ptr;
	}

	fprintf(stderr, "\nError in ArenaAllocAligned: reached arena end.\n");
	abort();
}

void* ArenaAlloc(Arena* arena, size_t size)
{
	return ArenaAllocAligned(arena, size, DEFAULT_ALIGNMENT);
}

Arena ArenaCreate(void* buffer, size_t buffer_size)
{
	return (Arena) {
		.buffer = buffer, 
		.size = buffer_size, 
		.offset_ptr = (uintptr_t)buffer
	};
}

void ArenaDestroy(Arena* arena)
{
	free(arena->buffer);
	arena->offset_ptr = 0;
	arena->size = 0;
}