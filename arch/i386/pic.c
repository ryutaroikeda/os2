#include <assert.h>
#include "io.h"
#include "pic.h"
#include <stdbool.h>
#include <stdio.h>

enum {
    PIC_MASTER_COMMAND_PORT = 0x20
    , PIC_MASTER_DATA_PORT = 0x21
    , PIC_MASTER_OFFSET = 0x20
    , PIC_SLAVE_COMMAND_PORT = 0xa0
    , PIC_SLAVE_DATA_PORT = 0xa1
    , PIC_SLAVE_OFFSET = 0x28
    , PIC_SLAVE_END = PIC_SLAVE_OFFSET + 0x7
};

void pic_disable(void) {
    io_write(PIC_SLAVE_DATA_PORT, 0xff);
    io_wait();
    io_write(PIC_MASTER_DATA_PORT, 0xff);
    io_wait();
}

/* Mask the given irq. */
void pic_mask(uint8_t irq) {
    assert(PIC_MASTER_OFFSET <= irq);
    assert(irq <= PIC_SLAVE_END);

    uint16_t port;
    if (irq < PIC_SLAVE_OFFSET) {
        irq = (uint8_t) (irq - PIC_MASTER_OFFSET);
        port = PIC_MASTER_DATA_PORT;
    } else {
        irq = (uint8_t) (irq - PIC_SLAVE_OFFSET);
        port = PIC_SLAVE_DATA_PORT;
    }
    uint8_t mask = (uint8_t) (io_read(port) | (1 << irq));
    io_write(port, mask);
    io_wait();
}

void pic_unmask(uint8_t irq) {
    assert(PIC_MASTER_OFFSET <= irq);
    assert(irq <= PIC_SLAVE_END);

    uint16_t port;
    if (irq < PIC_SLAVE_OFFSET) {
        irq = (uint8_t) (irq - PIC_MASTER_OFFSET);
        port = PIC_MASTER_DATA_PORT;
    } else {
        irq = (uint8_t) (irq - PIC_SLAVE_OFFSET);
        port = PIC_SLAVE_DATA_PORT;
    }
    uint8_t mask = (uint8_t) (io_read(port) & ~(1 << irq));
    io_write(port, mask);
    io_wait();
}

/**
 * Remap irq from PIC so that it does not interfere with software interrupts.
 */
void pic_initialize(void) {
    io_write(PIC_MASTER_COMMAND_PORT, 0x11);
    io_write(PIC_SLAVE_COMMAND_PORT, 0x11);
    io_wait();
    io_write(PIC_MASTER_DATA_PORT, PIC_MASTER_OFFSET);
    io_write(PIC_SLAVE_DATA_PORT, PIC_SLAVE_OFFSET);
    io_wait();
    // Tell master that there is a slave at irq 2 by setting bit 2.
    io_write(PIC_MASTER_DATA_PORT, 0x4);
    // Tell slave its cascade identity is irq 2.
    io_write(PIC_SLAVE_DATA_PORT, 2);
    io_wait();
    io_write(PIC_MASTER_DATA_PORT, 1);
    io_write(PIC_SLAVE_DATA_PORT, 1);
    io_wait();
    pic_disable();
    const uint8_t master = io_read(PIC_MASTER_DATA_PORT);
    const uint8_t slave = io_read(PIC_SLAVE_DATA_PORT);
    assert(0xff == master);
    assert(0xff == slave);
}

