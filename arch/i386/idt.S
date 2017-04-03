.section .text
.global idt_load
idt_load:
    push %ebp
    mov %esp, %ebp
    mov 8(%esp), %eax
    lidt (%eax)
    mov %ebp, %esp
    pop %ebp
    ret

