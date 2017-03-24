#include <string.h>

void* memcpy(void* __restrict to, const void* __restrict from, size_t size) {
    for (size_t i = 0; i < size; i++) {
        ((char*) to)[i] = ((const char*) from)[i];
    }
    return to;
}

