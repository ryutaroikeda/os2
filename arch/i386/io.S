.global io_write
.global io_read
.global io_wait

io_write:
    push %ebp
    mov %esp, %ebp
    push %edx
    push %eax
    mov 8(%ebp), %dx
    mov 12(%ebp), %ax
    out %ax, %dx
    pop %eax
    pop %edx
    pop %ebp
    ret

io_read:
    push %ebp
    mov %esp, %ebp
    push %edx
    mov 8(%ebp), %dx
    in %dx, %ax
    pop %edx
    pop %ebp
    ret

io_wait:
    mov $0, %ax
    mov $0x80, %dx
    out %ax, %dx
    ret

