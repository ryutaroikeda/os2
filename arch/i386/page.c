#include <assert.h>
#include "page.h"
#include <stdio.h>

/*
struct page_directory_entry page_directory[1024]
__attribute__((aligned(4096)));

struct page_table_entry page_table_0[1024] __attribute__((aligned(4096)));
*/

extern void page_load_directory(uint32_t*);

extern void page_enable(void);

void page_map(uint32_t* src, uint32_t* dst, size_t size) {
    (void) src;
    (void) dst;
    (void) size;
}

void page_initialize(void) {
    assert(4 == sizeof(struct page_directory_entry));
    assert(4 == sizeof(struct page_table_entry));
    //assert(! (0xfff & (uint32_t) page_directory));
    //assert(! (0xfff & (uint32_t) page_table_0));
}

