#ifndef _ARCH_I386_MEMORY_H
#define _ARCH_I386_MEMORY_H

#include <kernel/multiboot.h>

void memory_initialize(multiboot_info_t*);

void* memory_physical_to_virtual_address(void* p);

#endif
