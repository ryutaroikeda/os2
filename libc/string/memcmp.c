#include <string.h>

int memcmp(const void* a1, const void* a2, size_t size) {
    for (size_t i = 0; i < size; i++) {
        int diff = ((const unsigned char*)a1)[i] -
            ((const unsigned char*)a2)[i];
        if (diff) { return diff; }
    }
    return 0;
}

