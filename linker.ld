/* The bootloader will start execution at this symbol. */
ENTRY(_start)

SECTIONS {
	/* Begin at 1 MiB because it's conventional. */
	. = 1M;


	.text BLOCK(4K) : ALIGN(4K) {
		*(.multiboot)
		*(.text)
	}

	/* Read-only data. */
	.rodata BLOCK(4K) : ALIGN(4K) {
		*(.rodata)
	}

	/* Initialized read-write data. */
	.data BLOCK(4K) : ALIGN(4K) {
		*(.data)
	}

	/* Uninitialized read-write data and stack. */
	.bss BLOCK(4K) : ALIGN(4K) {
		/* Uninitialized globals go here. */
		*(COMMON)
		*(.bss)
	}
}

