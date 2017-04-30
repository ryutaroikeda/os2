#include "memory.h"
#include "memory_def.h"

#include <kernel.h>
#include <stdint.h>

void* memory_physical_to_virtual_address(void* p) {
    return (void*) ((uintptr_t)p + KERNEL_VIRTUAL_BASE);
}

/** mbi is a physical address. */
void memory_initialize(multiboot_info_t* mbi) {
    if (! (mbi->flags & 0x20)) {
        panic("no memory map provided by grub");
    }
}
