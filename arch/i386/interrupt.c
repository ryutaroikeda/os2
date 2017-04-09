#include <assert.h>
#include "gdt.h"
#include "idt.h"
#include "interrupt.h"
#include <kernel.h>
#include <kernel/interrupt.h>
#include <macro/repeat.h>
#include <stdio.h>
#include <stdlib.h>

struct idt_gate idt_gates[IDT_GATE_SIZE];

struct idt_pointer idt_pointer = {
        .limit = sizeof(idt_gates) - 1,
        .base = (uint32_t) idt_gates
};

/* Register handlers written in C with interrupt_set_handler. */
struct interrupt_handler interrupt_handlers[IDT_GATE_SIZE];

/* Pointers to assembly code that set up the call to
 * interrupt_handle. See interrupt_entry.S */
void* interrupt_entry_with_error_code[IDT_GATE_SIZE];
void* interrupt_entry_without_error_code[IDT_GATE_SIZE];

#define DECLARE_INTERRUPT_ENTRY(IRQ) \
    extern void* interrupt_entry_with_error_code_ ## IRQ; \
    extern void* interrupt_entry_without_error_code_ ## IRQ;
REPEAT_255(DECLARE_INTERRUPT_ENTRY)

static void interrupt_handle_default(const struct interrupt_stack* s) {
    (void) s;
    panic("unregistered interrupt handler called");
}

static void interrupt_handle_divide_fault(const struct interrupt_stack* s) {
    (void) s;
    panic("division by zero");
}

/*
static void interrupt_handle_segment_not_set_fault(
        const struct interrupt_stack* s) {
    (void) s;
    panic("segment not present");
}

static void interrupt_handle_general_protection_fault(
        const struct interrupt_stack* s) {
    (void) s;
    panic("general protection fault");
}
*/

void interrupt_initialize(void) {
    assert(6 == sizeof(struct idt_pointer));
    assert(8 == sizeof(struct idt_gate));
#define SET_INTERRUPT_ENTRY(IRQ) \
    interrupt_entry_with_error_code[IRQ] = \
        &interrupt_entry_with_error_code_ ## IRQ; \
    interrupt_entry_without_error_code[IRQ] = \
        &interrupt_entry_without_error_code_ ## IRQ;
    REPEAT_255(SET_INTERRUPT_ENTRY)
    for (uint32_t irq = 0; irq < IDT_GATE_SIZE; irq++) {
        interrupt_set_handler(irq, interrupt_handle_default, false, false);
    }
    idt_load(&idt_pointer);

    interrupt_set_handler(0, interrupt_handle_divide_fault, false, true);
    /*
    interrupt_set_handler(11, interrupt_handle_segment_not_set_fault, true,
            true);
            */
 //   interrupt_set_handler(13, interrupt_handle_general_protection_fault,
   //         true, true);
    interrupt_enable();
}

static struct idt_gate idt_gate(uint32_t offset) {
    return (struct idt_gate) {
        .offset_lo = offset & 0xffff,
        .offset_hi = (uint16_t) (offset >> 16),
        .selector = GDT_CODE_SEGMENT,
        .zero = 0,
        .gate_type = IDT_GATE_TYPE_INTERRUPT_32,
        .storage_segment = 0,
        .privilege = 0,
        .present = true
    };
}

void interrupt_set_handler(uint32_t irq, interrupt_handler handler,
        bool error_code, bool present) {
    if (error_code) {
        idt_gates[irq] = idt_gate(
                (uint32_t) interrupt_entry_with_error_code[irq]);
    } else {
        idt_gates[irq] = idt_gate(
                (uint32_t) interrupt_entry_without_error_code[irq]);
    }
    interrupt_handlers[irq] = (struct interrupt_handler) {
        .callback = handler,
        .present = present
    };
}

void interrupt_handle(const struct interrupt_stack* stack, uint32_t irq) {
    if (! interrupt_handler_present(irq)) {
        panic("no handler for irq %d", irq);
    }
    interrupt_handlers[irq].callback(stack);
}

bool interrupt_handler_present(uint32_t irq) {
    return interrupt_handlers[irq].present;
}

