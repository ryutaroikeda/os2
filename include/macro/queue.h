#ifndef _MACRO_QUEUE_H
#define _MACRO_QUEUE_H

#include <assert.h>

/**
 * Declare and define a queue for the given struct.
 * This won't work for immutable structs.
 */

#define QUEUE_DECLARE(type, size) \
    struct type ## _queue { \
        struct type queue[size + 1]; \
        int start; \
        int end; \
        int error; \
    }; \
    void type ## _queue_enqueue( \
            struct type ## _queue*, struct type); \
    struct type type ## _queue_dequeue(struct type ## _queue*); \
    int type ## _queue_is_empty(struct type ## _queue*); \
    struct swallow_semicolon_after_declare ## type { int a; }

#define QUEUE_DEFINE(type, size) \
    void type ## _queue_enqueue( \
            struct type ## _queue* q, struct type t) { \
        assert(q->end != ((q->start - 1) % (size + 1))); \
        q->queue[q->end] = t; \
        q->end = (q->end + 1) % (size + 1); \
    } \
    struct type type ## _queue_dequeue(struct type ## _queue* q) { \
        assert(q->start != q->end); \
        struct type result = q->queue[q->start]; \
        q->start = (q->start + 1) % (size + 1); \
        return result; \
    } \
    int type ## _queue_is_empty(struct type ## _queue* q) { \
        return q->start == q->end; \
    } \
    struct swallow_semicolon_after_define ## type { int a; }

#endif
