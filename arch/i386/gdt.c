#include <assert.h>
#include "gdt.h"

struct gdt_descriptor gdt[3];

struct gdt_pointer gdt_pointer = {
    .limit = sizeof(gdt) - 1,
    .base = (uint32_t) gdt
};

void gdt_initialize(void) {
    assert(sizeof(struct gdt_descriptor) == 8);
    gdt[0] = (struct gdt_descriptor) {0};
    gdt[1] = gdt_descriptor(0, 0xfffff, 0x9a, 0xc);
    gdt[2] = gdt_descriptor(0, 0xfffff, 0x92, 0xc);
    gdt_load(&gdt_pointer);
}

struct gdt_descriptor
gdt_descriptor(uint32_t base, uint32_t limit, uint8_t access,
        uint8_t granularity) {
    return (struct gdt_descriptor) {
        .base_lo = base & 0xffff,
        .base_mid = (base >> 16) & 0xff,
        .base_hi = (uint8_t) ((base >> 24) & 0xff),
        .limit_lo = limit & 0xffff,
        .access = access,
        .granularity = (uint8_t) ((granularity << 4) |
            (int) ((limit >> 16) & 0xf))
    };
}

