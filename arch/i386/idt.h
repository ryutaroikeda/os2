#ifndef _ARCH_I386_IDT_H
#define _ARCH_I386_IDT_H

#include <stdint.h>

enum {
    IDT_GATE_SIZE = 256,
    IDT_GATE_TYPE_INTERRUPT_32 = 0xe
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
    uint8_t privilege : 2;
    uint8_t present: 1;
    uint16_t offset_hi;
} __attribute__((packed));

void idt_load(const struct idt_pointer*);

#endif

