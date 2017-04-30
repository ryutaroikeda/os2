#ifndef _ARCH_I386_PAGE_H
#define _ARCH_I386_PAGE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct page_directory_entry {
    bool present: 1;
    bool writable: 1;
    bool user: 1;
    bool write_through: 1;
    bool disable_cache: 1;
    bool accessed: 1;
    bool zero: 1;
    bool page_size: 1;
    bool ignored: 1;
    uint32_t free_to_use: 3;
    uint32_t table_offset: 20;
} __attribute__((packed));

struct page_table_entry {
    bool present: 1;
    bool writable: 1;
    bool user: 1;
    bool write_through: 1;
    bool disable_cache: 1;
    bool accessed: 1;
    bool dirty: 1;
    bool zero: 1;
    bool global: 1;
    uint32_t free_to_use: 3;
    uint32_t physical_address: 20;
} __attribute__((packed));

void page_initialize(void);

void page_map(uint32_t* src, uint32_t* dst, size_t size);

void page_enable(void);

void page_enable_size_extension(void);

void page_load_directory(uint32_t*);

#endif
