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
.type gdt_load, @function
.global gdt_load
gdt_load:
    mov 8(%esp), %eax
    # testing
    mov $gdt_descriptor, %eax
    lgdt (%eax)
    ret

.section .text
.type gdt_reset_segment_registers, @function
.global gdt_reset_segment_registers
gdt_reset_segment_registers:
    # Assume second GDT entry is code segment. Set %cs with a far return.
    jmp $0x8, $gdt_reset_segment_registers_end
gdt_reset_segment_registers_end:
    # Assume third GDT entry is data segment.
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    ret

