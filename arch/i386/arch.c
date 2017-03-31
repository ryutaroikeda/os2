#include <kernel/arch.h>
#include <kernel/terminal.h>

extern void gdt_initialize(void);

extern void page_initialize(void);

extern void idt_initialize(void);

void arch_initalize(void) {
    terminal_initialize();
    page_initialize();
    gdt_initialize();
    idt_initialize();
}

