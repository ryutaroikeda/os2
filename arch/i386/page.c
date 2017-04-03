#include "page.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

uint32_t page_directory[1024] __attribute__((aligned(4096)));

// make one page table
uint32_t page_table[1024] __attribute__((aligned(4096)));

extern void page_load_directory(uint32_t*);

extern void page_enable(void);

void page_initialize(void) {
    for (size_t i = 0; i < 1024; i++) {
        // enable read and write
        page_directory[i] = 2;
    }
    for (size_t i = 0; i < 1024; i++) {
        // present, and can read and write
        page_table[i] = (i * 0x1000) | 3;
    }
    page_directory[0] = (uint32_t) page_table | 3;

    page_load_directory(page_directory);
    page_enable();
}

