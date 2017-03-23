# default CFLAGS
CFLAGS?=-O2 -g

SYSROOT?=

# mandatory CFLAGS
CFLAGS:=$(CFLAGS) -Wextra -Wall -pedantic -Werror -Wshadow -Wpointer-arith \
	-Wcast-qual -Wstrict-prototypes -Wmissing-prototypes -Wconversion \
	-ffreestanding -std=gnu99

ARCH?=i386
ARCHDIR=arch/$(ARCH)
ARCH2=i686

C_SOURCES = $(wildcard kernel/*.c $(ARCHDIR)/*.c libc/stdio/*.c \
			libc/string/*.c)
ASM_SOURCES = $(wildcard $(ARCHDIR)/*.s)
C_OBJ = $(C_SOURCES:.c=.o)
ASM_OBJ = $(ASM_SOURCES:.s=.o)

HEADER_DIRS=kernel libc

.PHONY: clean
.PHONY: tags

install-headers:
	for header_dir in $(HEADER_DIRS) ; do \
		mkdir -p sysroot/usr/include; \
		cp -r --preserve=timestamps $$header_dir/include/* \
			sysroot/usr/include/ ; \
	done

clean:
	-rm $(C_OBJ) $(ASM_OBJ)
	-rm os.bin
	-rm os.iso
	-rm -rf isodir
	-rm -rf sysroot
	-rm tags

tags:
	ctags -R --exclude=isodir .

%.o: %.s
	$(AS) $< -o $@

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

os.bin: $(ARCHDIR)/linker.ld $(C_OBJ) $(ASM_OBJ)
	$(CC) -T $< -o $@ -ffreestanding -O2 -nostdlib $^ -lgcc
	grub-file --is-x86-multiboot $@

os.iso: grub.cfg os.bin
	mkdir -p isodir/boot/grub
	cp os.bin isodir/boot/os.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o $@ isodir

