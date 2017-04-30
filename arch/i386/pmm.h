#ifndef _ARCH_I386_PMM_H
#define _ARCH_I386_PMM_H

void pmm_initialize(void);

void* pmm_alloc(void);

void pmm_free(void*);

#endif
