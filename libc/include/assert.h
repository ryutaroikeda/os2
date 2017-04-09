#ifndef _LIBC_ASSERT_H
#define _LIBC_ASSERT_H

#ifndef NDEBUG

#include <stdio.h>
#include <stdlib.h>

#define assert(condition) if (! (condition)) { \
    printf("%s:%d:%s: assert failed: %s\n", __FILE__, __LINE__, __func__, \
#condition); abort(); }

#else

#define assert(ignore) ((void)0)

#endif
#endif
