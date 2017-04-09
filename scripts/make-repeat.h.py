#!/usr/bin/env python

print('#ifndef _INCLUDE_REPEAT_H')
print('#define _INCLUDE_REPEAT_H')
print('#define REPEAT_0(M) M(0)')
for i in range(1, 256):
    print('#define REPEAT_{}(M) M({}) REPEAT_{}(M)'.format(i, i, i - 1))
print('#endif')
