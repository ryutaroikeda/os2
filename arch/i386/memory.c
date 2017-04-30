#include "memory.h"
#include "memory_def.h"

#include <kernel.h>
#include <stdint.h>
#include <stdio.h>

enum {
    MEMORY_MAP_SIZE = 16
};

enum memory_type {
    MEMORY_TYPE_USABLE_RAM = 1
};

static memory_map_t memory_map[MEMORY_MAP_SIZE];

static size_t memory_map_size = 0;

void* memory_physical_to_virtual_address(const void* p) {
    return (void*) ((uintptr_t)p + KERNEL_VIRTUAL_BASE);
}

void memory_initialize(const multiboot_info_t* mbi) {
    if (! (mbi->flags & 0x20)) {
        panic("no memory map provided by grub");
    }
    /** mbi and the addresses it contains are physical. */
    memory_map_t* mmap = (memory_map_t*)
        memory_physical_to_virtual_address((const void*)mbi->mmap_addr);
    const memory_map_t* mmap_end = (memory_map_t*)
        memory_physical_to_virtual_address((const void*)(mbi->mmap_addr +
                    mbi->mmap_length));
    memory_map_size = 0;
    while (mmap < mmap_end) {
        printf("base: %x_%x    limit: %x_%x    type:%u\n",
                mmap->base_addr_high, mmap->base_addr_low,
                mmap->length_high, mmap->length_low,
                mmap->type);
        if (MEMORY_TYPE_USABLE_RAM == mmap->type) {
            memory_map[memory_map_size] = *mmap;
            if (MEMORY_MAP_SIZE <= ++memory_map_size) { break; }
        }
        // Skip to the next memory map. GRUB treats .base_addr_low as offset 0
        // in memory_map and .size does not include the size of itself, so add
        // sizeof(.size) to account for this.
        mmap = (memory_map_t*)
            ((uintptr_t)mmap + mmap->size + sizeof(mmap->size));
    }
    printf("exit memory_initialize\n");
}

const memory_map_t* memory_get_map(void) {
    return memory_map;
}

size_t memory_get_map_size(void) {
    return memory_map_size;
}
