.macro interrupt_entry_with_error_code from, to
.section .text
.global interrupt_entry_with_error_code_(\from)
interrupt_entry_with_error_code_(\from):
    pushl \from
    jmp interrupt_common_handler
.if \to - \from
interrupt_entry_with_error_code "(\from + 1)", \to
.endif
.endm

.macro interrupt_entry_without_error_code from, to
.section .text
.global interrupt_entry_without_error_code_(\from)
interrupt_entry_without_error_code_(\from):
// push dummy error code
    pushl $0
    pushl \from
    jmp interrupt_common_handler
.if \to - \from
interrupt_entry_without_error_code "(\from + 1)", \to
.endif
.endm

.section .text
.global interrupt_enable
interrupt_enable:
	sti
	ret

.section .text
.global interrupt_disable
interrupt_disable:
	cli
	ret

.section .text
.global interrupt_load_table
interrupt_load_table:
	push %ebp
	mov %esp, %ebp
	mov 8(%esp), %eax
	lidt (%eax)
	mov %ebp, %esp
	pop %ebp
	ret

.global interrupt_common_handler
interrupt_common_handler:
    pushal

    // todo call registered interrupt handler

    popal
    /* Assume stack has irq and error code. Remove them from stack. */
    add $8, %esp

    iret

