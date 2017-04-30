#include "interrupt.h"
#include "io.h"
#include <kernel.h>
#include "keyboard.h"
#include "pic.h"

enum {
    KEYBOARD_IRQ = 0x21
};

static void keyboard_interrupt(const struct interrupt_stack* s) {
    (void) s;
    panic("keyboard handler not implemented yet");
}

void keyboard_initialize(void) {
    interrupt_set_handler(KEYBOARD_IRQ, keyboard_interrupt, false, true);
    //pic_unmask(KEYBOARD_IRQ);
}

