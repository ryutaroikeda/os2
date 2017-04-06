#include "idt.h"
#include "interrupt.h"
#include <macro/repeat.h>

struct idt_pointer idt_pointer;

struct idt_gate idt_gate[idt_gate_size];

void* interrupt_entry_with_error_code[idt_gate_size];
void* interrupt_entry_without_error_code[idt_gate_size];

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
}

void interrupt_register_handler(size_t irq, bool error_code,
        interrupt_handler* handler) {
    (void) irq;
    (void) error_code;
    (void) handler;
}
