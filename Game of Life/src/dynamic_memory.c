#include <stdio.h>
#include <stdlib.h>

void* SafeMalloc(size_t size)
{
	void* buffer = malloc(size);
	if (buffer == NULL) {
		fprintf(stderr, "Error in SafeMalloc: failed to allocate %zu bytes.\n", size);
		abort();
	}
	return buffer;
}

void* SafeCalloc(size_t count, size_t size)
{
	void* buffer = calloc(count, size);
	if (buffer == NULL) {
		fprintf(stderr, "Error in SafeCalloc: failed to allocate %zu bytes.\n", count * size);
		abort();
	}
	return buffer;
}

void* SafeRealloc(void* block, size_t size) {
	void* buffer = realloc(block, size);
	if (buffer == NULL) {
		fprintf(stderr, "Error in SafeRealloc: failed to reallocate block %p of %zu bytes.\n", block, size);
		abort();
	}
	return buffer;
}
