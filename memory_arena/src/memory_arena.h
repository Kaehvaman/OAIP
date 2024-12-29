#pragma once

#include <stdint.h>
#include <stddef.h>

#define ARENA_ALIGNMENT(type) offsetof(struct { char c; type x; }, x) // generates C4116 warning

#ifndef DEFAULT_ALIGNMENT
#define DEFAULT_ALIGNMENT (2 * sizeof(void*))
#endif

typedef struct {
	void* buffer;
	size_t size;
	uintptr_t offset_ptr;
} Arena;

Arena ArenaInit(size_t buffer_size);
void* ArenaAlloc(Arena* arena, size_t size);
void* ArenaAllocAligned(Arena* arena, size_t size, size_t alignment);
