#ifndef _ARCH_I386_GDT_H
#define _ARCH_I386_GDT_H

#include <stdbool.h>
#include <stdint.h>

struct gdt_pointer {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct gdt_segment {
    uint16_t limit_lo;
    uint16_t base_lo;
    uint8_t base_mid;
    uint8_t accessed: 1;
    uint8_t readable_writable: 1;
    uint8_t direction_conforming: 1;
    uint8_t executable: 1;
    uint8_t one: 1;
    uint8_t privilege: 2;
    uint8_t present: 1;
    uint8_t limit_hi: 4;
    uint8_t zero: 2;
    uint8_t size: 1;
    uint8_t granularity: 1;
    uint8_t base_hi;
} __attribute__((packed));

void gdt_initialize(void);

void gdt_load(struct gdt_pointer*);

struct gdt_segment
gdt_segment(uint32_t limit, uint32_t base, bool executable);

void gdt_reset_segment_registers(void);

#endif
