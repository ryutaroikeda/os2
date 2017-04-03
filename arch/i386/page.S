.section .text
.global page_load_directory
.type page_load_directory, @function
page_load_directory:
    push %ebp
    mov %esp, %ebp
    mov 8(%esp), %eax
    mov %eax, %cr3
    mov %ebp, %esp
    pop %ebp
    ret

.section .text
.global page_enable
.type page_enable, @function
page_enable:
    push %ebp
    mov %esp, %ebp
    mov %eax, %cr0
    or %eax, 0x80000001
    mov %eax, %cr0
    mov %ebp, %esp
    pop %ebp
    ret

