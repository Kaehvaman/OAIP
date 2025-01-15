#pragma once

void* SafeMalloc(size_t size);
void* SafeCalloc(size_t count, size_t size);
void* SafeRealloc(void* block, size_t size);
