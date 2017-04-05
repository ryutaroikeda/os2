#ifndef _ARCH_I386_GDT_H
#define _ARCH_I386_GDT_H

#include <stdbool.h>
#include <stdint.h>

struct gdt_pointer {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct gdt_descriptor {
    uint16_t limit_lo;
    uint16_t base_lo;
    uint8_t base_mid;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_hi;
} __attribute__((packed, aligned(8)));

void gdt_initialize(void);

void gdt_load(struct gdt_pointer*);

struct gdt_descriptor
gdt_descriptor(uint32_t limit, uint32_t base, uint8_t access,
        uint8_t granularity);

#endif
