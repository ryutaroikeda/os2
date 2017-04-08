#ifndef _ARCH_I386_INTERRUPT_H
#define _ARCH_I386_INTERRUPT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct interrupt_stack {
    uint32_t error_code;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
} __attribute__((packed));

typedef void (*interrupt_handler)(const struct interrupt_stack*);

void interrupt_initialize(void);

void interrupt_register_handler(size_t irq, interrupt_handler,
        bool error_code, bool present);

void interrupt_handle(const struct interrupt_stack*, size_t irq);

void interrupt_enable(void);
void interrupt_disable(void);

bool interrupt_handler_present(size_t irq);

#endif

