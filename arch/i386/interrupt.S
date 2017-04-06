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
	mov 4(%esp), %eax
	lidt (%eax)
	ret

.global interrupt_common_handler
interrupt_common_handler:
    pushal

    // todo call registered interrupt handler

    popal
    /* Assume stack has irq and error code. Remove them from stack. */
    add $8, %esp

    iret

