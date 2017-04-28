.section .text
.global page_load_directory
.type page_load_directory, @function
page_load_directory:
    mov 4(%esp), %eax
    mov %eax, %cr3
    ret

.section .text
.global page_enable
.type page_enable, @function
page_enable:
    mov %eax, %cr0
    or %eax, 0x80000001
    mov %eax, %cr0
    ret

