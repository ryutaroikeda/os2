#include "interrupt.h"
#include <kernel/arch.h>
#include <kernel/terminal.h>
#include "gdt.h"
#include "page.h"

#include <stdio.h>
#include <stdlib.h>

void arch_initialize(void) {
    terminal_initialize();
    gdt_initialize();
    interrupt_initialize();
    return;
    page_initialize();
}

