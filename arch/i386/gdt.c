#include "gdt.h"
#include <stdio.h>

struct gdt_segment gdt[3];

struct gdt_pointer gdt_pointer = {
    .limit = sizeof(gdt) - 1,
    .base = (uint32_t) gdt
};

void gdt_initialize(void) {
    gdt[0] = (struct gdt_segment) {0};
    gdt[1] = gdt_segment(0xfffff, 0, 1);
    gdt[2] = gdt_segment(0xfffff, 0, 0);
    gdt_load(&gdt_pointer);
    gdt_reset_segment_registers();
    printf("exit gdt_initialize()\n");
}

struct gdt_segment
gdt_segment(uint32_t limit, uint32_t base, bool executable) {
    return (struct gdt_segment) {
        .limit_lo = limit & 0xffff,
        .limit_hi = (limit >> 16) & 0xf,
        .base_lo = base & 0xffff,
        .base_mid = (base >> 16) & 0xff,
        .executable = executable,
        .one = 1,
        .privilege = 0,
        .accessed = 0,
        .readable_writable = 1,
        .direction_conforming = 0,
        .present = 1,
        .zero = 0,
        .size = 1,
        .granularity = 1,
        .base_hi = (uint8_t) ((base >> 24) & 0xff)
    };
}

