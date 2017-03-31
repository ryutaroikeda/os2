#ifndef _ARCH_I386_INTERRUPT_H
#define _ARCH_I386_INTERRUPT_H

struct interrupt_stack {
    uint32_t eax;
};

typedef void (*interrupt_handler)(const struct interrupt_stack*, size_t irq);

void interrupt_register_handler(size_t irq, bool has_error_code,
        interrupt_handler*);

#endif

