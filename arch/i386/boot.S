#include "memory_def.h"

// Declare constants for multiboot header.
// Align loaded modules on page boundaries.
.set ALIGN, 1 << 0
// Provide memory map.
.set MEMINFO, 1 << 1
.set FLAGS, ALIGN | MEMINFO
.set MAGIC, 0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

// Page directory index for kernel page.
.set KERNEL_PAGE_NUMBER, KERNEL_VIRTUAL_BASE >> 22

// Declare multiboot header in the multiboot 1 standard.
// The boot loader will look for the header in the first 8 kiB of the kernel
// aligned at a 32-bit boundary.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

// Allocate 16 kiB to the 16-byte aligned stack
.section .bss, "aw", @nobits
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .data
.align 0x1000

BOOT_PAGE_DIRECTORY:
// Temporary page directory entry to identity-map the first 4 MiB of the 32 bit
// physical address space. We have this here so that when we enable paging, we
// don't crash.
// Add more page tables as needed if kernel is too big to fit (more than
// 3 MiB). The bits set are 4MiB, read-write and present.
.long 0x00000083
// Pages before kernel space.
.rept KERNEL_PAGE_NUMBER - 1
.long 0
.endr
// A page for the kernel.
.long 0x00000083
// Fill in rest of page directory.
.rept 1024 - KERNEL_PAGE_NUMBER - 1
.long 0
.endr

// Entry point of the kernel
.section .text
.global _start
.type _start, @function
_start:
	// We are in 32 bit protected mode on an x86 machine.
	// Interrupts are disabled.

	// Load page directory. Use the physical address.
	mov $(BOOT_PAGE_DIRECTORY - KERNEL_VIRTUAL_BASE), %ecx
	mov %ecx, %cr3

	// Enable page size extension.
	mov %cr4, %ecx
	or $0x10, %ecx
	mov %ecx, %cr4

	// Enable paging.
	mov %cr0, %ecx
	or $0x80000000, %ecx
	mov %ecx, %cr0

	lea start_in_higher_half, %ecx
	jmp %ecx

start_in_higher_half:
	// Unmap identity map.
	movl $0, BOOT_PAGE_DIRECTORY
	invlpg 0

	// Set up the stack.
	mov $stack_top, %esp

	// multiboot magic number
	push %eax
	// ebx has physical address of multiboot info structure (mbi). Pointers
	// inside mbi are also physical.
	push %ebx

	call kernel_main

    // Disable interrupts.
	cli
	// Loop forever.
1:  hlt
	jmp 1b

.global start
.set start, _start - KERNEL_VIRTUAL_BASE

