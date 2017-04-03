# Declare constants for multiboot header.
# Align loaded modules on page boundaries.
.set ALIGN, 1 << 0
# Provide memory map.
.set MEMINFO, 1 << 1
.set FLAGS, ALIGN | MEMINFO
.set MAGIC, 0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

# Declare multiboot header in the multiboot 1 standard.
# The boot loader will look for the header in the first 8 kiB of the kernel
# aligned at a 32-bit boundary.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Allocate 16 kiB to the 16-byte aligned stack
.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

# Entry point of the kernel
.section .text
.global _start
.type _start, @function
_start:
	# We are in 32 bit protected mode on an x86 machine.
	# Interrupts are disabled.

	# Set up the stack.
	mov $stack_top, %esp

	call kernel_main

	# Loop forever.
	cli
1:  hlt
	jmp 1b

# Set the size of the _start function to the current location minus the
# location of start. Apparently this makes it easier to debug.
.size _start, . - _start

