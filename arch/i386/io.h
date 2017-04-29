#ifndef _ARCH_I386_IO_H
#define _ARCH_I386_IO_H

#include <stdint.h>

void io_write(uint16_t port, uint8_t data);

uint8_t io_read(uint16_t port);

void io_wait(void);

#endif

