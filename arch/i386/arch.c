#include "gdt.h"
#include <kernel/arch.h>
#include <kernel/interrupt.h>
#include <kernel/multiboot.h>
#include <kernel/terminal.h>
#include "keyboard.h"
#include "memory.h"
#include "page.h"
#include "pic.h"
#include "pmm.h"
#include <stdio.h>
#include <stdlib.h>

void arch_initialize(multiboot_info_t* mbi) {
    page_initialize();
    terminal_initialize();
    gdt_initialize();
    pic_initialize();
    interrupt_initialize();
    memory_initialize((multiboot_info_t*)
            memory_physical_to_virtual_address(mbi));
    pmm_initialize();
    keyboard_initialize();
}

