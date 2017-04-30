.section .text
.global io_write
.global io_read
.global io_wait

io_write:
    push %ebp
    mov %esp, %ebp
    mov 8(%ebp), %dx
    mov 12(%ebp), %al
    out %al, %dx
    pop %ebp
    ret

io_read:
    push %ebp
    mov %esp, %ebp
    mov 8(%ebp), %dx
    in %dx, %al
    pop %ebp
    ret

io_wait:
    mov $0x80, %dx
    mov $0, %al
    out %al, %dx
    ret

