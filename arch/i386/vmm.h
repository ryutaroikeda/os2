#ifndef _ARCH_I386_VMM_H
#define _ARCH_I386_VMM_H

void vmm_initialize(void);

void* vmm_alloc(void);

void vmm_free(void*);

#endif
