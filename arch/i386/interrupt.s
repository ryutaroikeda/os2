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

.global interrupt_enable
interrupt_enable:
    sti
    ret

.global interrupt_disable
interrupt_disable:
    cli
    ret

.global interrupt_common_handler
interrupt_common_handler:
    
