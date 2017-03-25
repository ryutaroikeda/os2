#include <string.h>

void* memset(void* block, int c, size_t size) {
    for (size_t i = 0; i < size; i++) {
        ((unsigned char*)block)[i] = (unsigned char) c;
    }
    return block;
}

