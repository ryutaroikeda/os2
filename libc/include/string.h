#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>

size_t strlen(const char*);

int memcmp(const void* a1, const void* a2, size_t size);

void* memcpy(void* __restrict to, const void* __restrict from, size_t size);

void* memmove(void* to, const void* from, size_t size);

void* memset(void* block, int c, size_t size);

#endif

