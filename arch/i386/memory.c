#include "memory.h"
#include "memory_def.h"

#include <kernel.h>
#include <stdint.h>
#include <stdio.h>

void* memory_physical_to_virtual_address(const void* p) {
    return (void*) ((uintptr_t)p + KERNEL_VIRTUAL_BASE);
}

/** mbi is a physical address. */
void memory_initialize(const multiboot_info_t* mbi) {
    if (! (mbi->flags & 0x20)) {
        panic("no memory map provided by grub");
    }
    memory_map_t* mmap = (memory_map_t*)
        memory_physical_to_virtual_address((const void*)mbi->mmap_addr);
    const memory_map_t* mmap_end = (memory_map_t*)
        memory_physical_to_virtual_address((const void*)(mbi->mmap_addr +
                    mbi->mmap_length));
    int count = 0;
    while (mmap < mmap_end) {
        printf("base: %x_%x    limit: %x_%x    type:%u\n",
                mmap->base_addr_high, mmap->base_addr_low,
                mmap->length_high, mmap->length_low,
                mmap->type);
        // Skip to the next memory map.
        // GRUB treats .base_addr_low as offset 0 in memory_map, so add
        // sizeof(.size) to account for this.
        mmap = (memory_map_t*)
            ((uintptr_t)mmap + mmap->size + sizeof(mmap->size));
        count++;
    }
    printf("exit memory_initialize: %d\n", count);
}
