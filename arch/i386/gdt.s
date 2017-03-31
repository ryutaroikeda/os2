.section .data
gdt_start:
gdt_null:
.long 0
.long 0
gdt_code:
.int 0xffff
.int 0
.byte 0
.byte 0b10011010
.byte 0b11001111
.byte 0
gdt_data:
.int 0xffff
.int 0
.byte 0
.byte 0b10010010
.byte 0b11001111
.byte 0
gdt_end:
gdt_descriptor:
.int gdt_end - gdt_start - 1
.long gdt_start

.section .text
.global gdt_initialize
gdt_initialize:
    lgdt (gdt_descriptor)
    # set up segment registers and do a far jump
    mov $0x08, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    jmp 0x08:gdt_initialize_end
gdt_initialize_end:
    ret

