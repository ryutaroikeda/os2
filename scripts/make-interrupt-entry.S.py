#!/usr/bin/env python

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

