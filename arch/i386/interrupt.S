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

.equ REGISTER_SIZE, 8

.global interrupt_common_handler
interrupt_common_handler:
    pushal
	mov %esp, %ebp

	/* Push the IRQ. */
	pushl (REGISTER_SIZE * 4)(%ebp)

	/* Push pointer to the interrupt stack. */
	mov %ebp, %eax
	add $((REGISTER_SIZE + 1)  * 4), %eax
	push %eax

	call interrupt_handle

	/* Clear arguments. */
	add $(2 * 4), %esp

    popal
    /* Assume stack has irq and error code. Remove them from stack. */
    add $8, %esp

    iret

