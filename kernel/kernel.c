#include <kernel/arch.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__linux__)
#error "You are not using a cross-compiler"
#endif

#if !defined(__i386__)
#error "You must use an ix86-elf compiler"
#endif

void kernel_main(void);
void kernel_main(void) {
    arch_initalize();
    char buf[] = "hello world\n";
    char* s = &buf[1];
    //memcpy(buf, "holaa", 5);

    memmove(s, buf, 2);
    //memset(s, 'h', 500);
    /*
    printf("%s", buf);
    if (0 == memcmp(buf, buf, 2)) {
        printf("eq\n");
    }
    */
    uint32_t* a;
    a = (uint32_t*)0x101fff111;
    *a = 2345;
    printf("%d\n", *a);
    printf("exit kernel\n");
}

