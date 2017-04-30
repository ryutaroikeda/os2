#ifndef _MACRO_SASSERT_H
#define _MACRO_SASSERT_H

/** Static assert. Make compile-time assertions. */

#define GLUE(a, b) _GLUE(a, b)
#define _GLUE(a, b) a ## b
#define sassert(condition) \
    typedef char GLUE(assertion_failed_, __COUNTER__)[(condition) ? 1 : -1]

#endif
