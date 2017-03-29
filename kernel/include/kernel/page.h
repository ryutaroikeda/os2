#ifndef _PAGE_H
#define _PAGE_H

#include <stdint.h>

void page_initialize(void);

void page_load_directory(uint32_t*);

void page_enable(void);

#endif

