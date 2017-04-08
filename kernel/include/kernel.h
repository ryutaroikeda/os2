#ifndef _KERNEL_H
#define _KERNEL_H

void panic(const char* format, ...);

/**
 * Do nothing.
 */
void idle(void);

#endif
