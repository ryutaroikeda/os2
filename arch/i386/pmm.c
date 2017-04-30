#include <assert.h>
#include <kernel.h>
#include "memory.h"
#include "pmm.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

enum {
    PMM_FRAME_SIZE = 4096
    , PMM_FRAME_MAX = 1 << 15
};

// The nth frame is free if the nth bit is zero.
static uint32_t frame_map[PMM_FRAME_MAX];

static size_t pmm_frame_count;

static void pmm_set_frame_map(size_t frame) {
    size_t size = sizeof(frame_map[0]) * 8;
    size_t offset = frame / size;
    size_t bit = frame % size;
    frame_map[offset] = (uint32_t) (frame_map[offset] | (uint32_t)(1 << bit));
}

static void pmm_unset_frame_map(size_t frame) {
    size_t size = sizeof(frame_map[0]) * 8;
    size_t offset = frame / size;
    size_t bit = frame % size;
    frame_map[offset] =
        (uint32_t) (frame_map[offset] & (uint32_t)~(1 << bit));
}

static size_t address_to_frame(uintptr_t p) {
    if (0 == p) { return 0; }
    return ((p - 1) / PMM_FRAME_SIZE) + 1;
}

static bool pmm_get_frame(size_t frame) {
    size_t size = sizeof(frame_map[0]) * 8;
    size_t offset = frame / size;
    size_t bit = frame % size;
    return frame_map[offset] & (uint32_t) (1 << bit);
}

void pmm_initialize(void) {
    memset(frame_map, 0xff, sizeof(frame_map));
    pmm_frame_count = 0;
    const memory_map_t* mmap = memory_get_map();
    const size_t mmap_size = memory_get_map_size();
    printf("%u memory blocks found\n", mmap_size);
    for (size_t i = 0; i < mmap_size; i++) {
        size_t frame = address_to_frame(mmap[i].base_addr_low);
        size_t end = address_to_frame(mmap[i].base_addr_low +
                mmap[i].length_low);
        printf("start: %u, end: %u\n", frame, end);
        while (frame < end) {
            pmm_unset_frame_map(frame++);
            pmm_frame_count++;
        }
    }
    printf("%u frames available\n", pmm_frame_count);
}

void* pmm_alloc(void) {
    for (size_t i = 0; i < PMM_FRAME_MAX; i++) {
        if (0 == pmm_get_frame(i)) {
            pmm_set_frame_map(i);
            pmm_frame_count--;
            return (void*) (i * PMM_FRAME_SIZE);
        }
    }
    panic("out of frames");
    return NULL;
}

void pmm_free(void* p) {
    size_t frame = address_to_frame((uintptr_t) p);
    assert(pmm_get_frame(frame));
    pmm_unset_frame_map(frame);
    pmm_frame_count++;
}
