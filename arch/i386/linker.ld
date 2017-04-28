/* The bootloader will start execution at this symbol. */
ENTRY(_start)
OUTPUT_FORMAT(elf32-i386)

/* Linker for higher-half kernel. */
SECTIONS {
	/* Put kernel at 3 GB + 1 MB in virtual address space.
     * This is mapped to 1 MB in physical address space. */
	. = 0xc0100000;

    _kernel_start = .;

    /* The relocation address is the address offset applied to the section.
     * The load address is where the section gets loaded. We take away the
     * kernel base from the load address because we map this back up to the
     * virtual address via the page table. */
    .text ALIGN(4K) : AT(ADDR(.text) - 0xc0000000) {
        *(.multiboot)
        *(.text)
    }
    .rodata ALIGN(4K) : AT(ADDR(.rodata) - 0xc0000000) {
        *(.rodata)
    }

	/* Initialized read-write data. */
	.data ALIGN(4K) : AT(ADDR(.data) - 0xc0000000) {
		*(.data)
	}

	/* Uninitialized read-write data and stack. */
	.bss ALIGN(4K) : AT(ADDR(.bss) - 0xc0000000) {
		/* Uninitialized globals go here. */
		*(COMMON)
		*(.bss)
	}

    _kernel_end = .;
}

