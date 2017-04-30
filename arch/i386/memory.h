#ifndef _ARCH_I386_MEMORY_H
#define _ARCH_I386_MEMORY_H

#include <kernel/multiboot.h>
#include <stddef.h>

void memory_initialize(const multiboot_info_t*);

void* memory_physical_to_virtual_address(const void* p);

const memory_map_t* memory_get_map(void);

size_t memory_get_map_size(void);

#endif
