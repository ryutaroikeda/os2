#include <string.h>

void* memmove(void* to, const void* from, size_t size) {
    if (to <= from) {
        for (size_t i = 0; i < size; i++) {
            ((char*) to)[i] = ((const char*) from)[i];
        }
    } else {
        for (size_t i = size; i > 0; i--) {
            ((char*) to)[i - 1] = ((const char*) from)[i - 1];
        }
    }
    return to;
}

