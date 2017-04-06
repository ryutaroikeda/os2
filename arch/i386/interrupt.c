#include "gdt.h"
#include "idt.h"
#include "interrupt.h"
#include <macro/repeat.h>

enum {
    INTERRUPT_GATE_TYPE_INTERRUPT_32 = 0xe
};

struct idt_pointer idt_pointer;

struct idt_gate idt_gates[IDT_GATE_SIZE];

interrupt_handler interrupt_handlers[IDT_GATE_SIZE];

void* interrupt_entry_with_error_code[IDT_GATE_SIZE];
void* interrupt_entry_without_error_code[IDT_GATE_SIZE];

#define DECLARE_INTERRUPT_ENTRY(IRQ) \
    extern void* interrupt_entry_with_error_code_ ## IRQ; \
    extern void* interrupt_entry_without_error_code_ ## IRQ;
REPEAT_255(DECLARE_INTERRUPT_ENTRY)

void interrupt_initialize(void) {
#define SET_INTERRUPT_ENTRY(IRQ) \
    interrupt_entry_with_error_code[IRQ] = \
        interrupt_entry_with_error_code_ ## IRQ; \
    interrupt_entry_without_error_code[IRQ] = \
        interrupt_entry_without_error_code_ ## IRQ;
    REPEAT_255(SET_INTERRUPT_ENTRY)
    for (size_t irq = 0; irq < IDT_GATE_SIZE; irq++) {
        interrupt_register_handler(irq, false, NULL, false);
    }
}

void interrupt_register_handler(size_t irq, interrupt_handler handler,
        bool error_code, bool present) {
    if (error_code) {
        idt_gates[irq] = (struct idt_gate) {
            .offset_lo =
                (size_t) interrupt_entry_with_error_code[irq] & 0xffff,
            .offset_hi = (uint16_t)
                ((size_t) interrupt_entry_with_error_code[irq] >> 16),
            .selector = GDT_CODE_SEGMENT,
            .zero = 0,
            .gate_type = INTERRUPT_GATE_TYPE_INTERRUPT_32,
            .storage_segment = 0,
            .descriptor_privilege_level = 0,
            .present = present
        };
    } else {
        idt_gates[irq] = (struct idt_gate) {
            .offset_lo =
                (size_t) interrupt_entry_without_error_code[irq] & 0xffff,
            .offset_hi = (uint16_t)
                ((size_t) interrupt_entry_without_error_code[irq] >> 16),
            .selector = GDT_CODE_SEGMENT,
            .zero = 0,
            .gate_type = INTERRUPT_GATE_TYPE_INTERRUPT_32,
            .storage_segment = 0,
            .descriptor_privilege_level = 0,
            .present = present
        };
    }
    interrupt_handlers[irq] = handler;
}

void interrupt_handle(const struct interrupt_stack* stack, size_t irq) {
    interrupt_handlers[irq](stack);
}
