CFLAGS=-Wextra -Wall -pedantic -Werror -Wshadow -Wpointer-arith \
	   -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes -Wconversion \
	   -ffreestanding -O2 -std=gnu99

test: os.bin
	grub-file --is-x86-multiboot $<

boot.o: boot.s
	i686-elf-as $< -o $@

kernel.o: kernel.c
	i686-elf-gcc -c $< -o $@ $(CFLAGS)

os.bin: linker.ld kernel.o boot.o
	i686-elf-gcc -T linker.ld -o $@ -ffreestanding -O2 -nostdlib boot.o \
		kernel.o -lgcc

os.iso: grub.cfg os.bin
	mkdir -p isodir/boot/grub
	cp os.bin isodir/boot/os.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o $@ isodir

.PHONY: test

