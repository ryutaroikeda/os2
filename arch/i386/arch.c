#include <kernel/arch.h>
#include <kernel/interrupt.h>
#include <kernel/multiboot.h>
#include <kernel/terminal.h>
#include "keyboard.h"
#include "gdt.h"
#include "memory.h"
#include "page.h"
#include "pic.h"

#include <stdio.h>
#include <stdlib.h>

void arch_initialize(multiboot_info_t* mbi) {
    terminal_initialize();
    gdt_initialize();
    pic_initialize();
    interrupt_initialize();
    memory_initialize((multiboot_info_t*)
            memory_physical_to_virtual_address(mbi));
    keyboard_initialize();
}

