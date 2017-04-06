#ifndef _ARCH_I386_IDT_H
#define _ARCH_I386_IDT_H

#include <stdint.h>

enum {
    idt_gate_size = 256
};

struct idt_pointer {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct idt_gate {
    uint16_t offset_lo;
    uint16_t selector;
    uint8_t zero;
    uint8_t gate_type: 4;
    uint8_t storage_segment: 1;
    uint8_t descriptor_privilege_level: 2;
    uint8_t present: 1;
    uint16_t offset_hi;
} __attribute__((packed));

void idt_load(const struct idt_pointer*);

#endif

