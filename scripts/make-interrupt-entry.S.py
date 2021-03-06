#!/usr/bin/env python
# This generates arch/i386/interrupt_entry.S
# Generates IDT entries for interrupts with and without error codes.
# Interrupts without error codes get a dummy zero on the stack so the
# interrupt_common_handler can treat them the same.

print('/* Generated by scripts/make-interrupt-entry.S.py */')
print('.section .text')

for i in range(0, 256):
    handler = 'interrupt_entry_with_error_code_{}'.format(i)
    print('.global {}'.format(handler))
    print('{}:'.format(handler))
    print('pushl ${}'.format(i))
    print('jmp interrupt_common_handler')

for i in range(0, 256):
    handler = 'interrupt_entry_without_error_code_{}'.format(i)
    print('.global {}'.format(handler))
    print('{}:'.format(handler))
    print('pushl $0')
    print('pushl ${}'.format(i))
    print('jmp interrupt_common_handler')

