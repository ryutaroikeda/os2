.section .text
.global page_load_directory
.type page_load_directory, @function
page_load_directory:
    mov 4(%esp), %eax
    mov %eax, %cr3
    ret

.global page_enable
.type page_enable, @function
page_enable:
    mov %eax, %cr0
    or %eax, 0x80000000
    mov %eax, %cr0
    ret

.global page_enable_size_extension
page_enable_size_extension:
    mov %cr4, %eax
    or $0x10, %eax
    mov %eax, %cr4
    ret

