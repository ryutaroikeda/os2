#ifndef _KERNEL_ARCH_H
#define _KERNEL_ARCH_H
/**
 * The target architecture must implement these.
 */

/**
 * Do architecture specific initialization.
 */
void arch_initialize(void);

/**
 * Do nothing.
 */
void idle(void);

#endif

