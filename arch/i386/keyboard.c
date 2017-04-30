#include "interrupt.h"
#include "io.h"
#include <kernel.h>
#include "keyboard.h"
#include <macro/queue.h>
#include "pic.h"

enum {
    KEYBOARD_IRQ = 0x21
};

struct keyboard_x {
    int a;
};

QUEUE_DECLARE(keyboard_x, 1);
QUEUE_DEFINE(keyboard_x, 10);

static void keyboard_interrupt(const struct interrupt_stack* s) {
    (void) s;
    panic("keyboard handler not implemented yet");
}

void keyboard_initialize(void) {
    interrupt_set_handler(KEYBOARD_IRQ, keyboard_interrupt, false, true);
    pic_unmask(KEYBOARD_IRQ);
}

