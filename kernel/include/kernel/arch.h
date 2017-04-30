#ifndef _KERNEL_ARCH_H
#define _KERNEL_ARCH_H

#include <kernel/multiboot.h>

/**
 * Do architecture specific initialization.
 */
void arch_initialize(multiboot_info_t*);

#endif

