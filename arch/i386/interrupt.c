#include "interrupt.h"

void interrupt_initialize(void) {
    
}

void interrupt_register_handler(size_t irq, bool error_code,
        interrupt_handler* handler) {
    (void) irq;
    (void) error_code;
    (void) handler;
}
