.section .text
.type gdt_load, @function
.global gdt_load
gdt_load:
    mov 4(%esp), %eax
    lgdt (%eax)
	# Assume third GDT entry is data segment.
    mov $0x10, %eax
    mov %eax, %ds
    mov %eax, %es
    mov %eax, %fs
    mov %eax, %gs
    mov %eax, %ss
    # Assume second GDT entry is code segment. Set %cs with a far return.
    jmp $0x8, $gdt_reset_segment_registers_end
gdt_reset_segment_registers_end:
    ret

