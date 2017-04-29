#ifndef _ARCH_I386_PIC_H
#define _ARCH_I386_PIC_H

#include <stdint.h>

// Programmable interrupt controller

void pic_initialize(void);

void pic_disable(void);

void pic_mask(uint8_t irq);

void pic_unmask(uint8_t irq);

#endif
