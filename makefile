MODULES:=libc kernel

CFLAGS?=-O2 -g
SYSROOT?=
PREFIX?=/usr
LDFLAGS?=
LIBS?=

CFLAGS:=$(CFLAGS) -Wextra -Wall -pedantic -Werror -Wshadow -Wpointer-arith \
	-Wcast-qual -Wstrict-prototypes -Wmissing-prototypes -Wconversion \
	-ffreestanding -std=gnu99 -Ikernel/include

LIBK_CFLAGS:=$(CFLAGS) -D__is_libk

ARCH?=i386
ARCHDIR:=arch/$(ARCH)

KERNEL_C:=$(wildcard kernel/*.c)
ARCH_C:=$(wildcard $(ARCHDIR)/*.c)
ARCH_S:=$(wildcard $(ARCHDIR)/*.s)
LIBK_C:=$(wildcard libc/stdio/*.c libc/string/*.c libc/stdlib/*.c)
KERNEL_OBJ:=$(KERNEL_C:.c=.o)
ARCH_OBJ:=$(ARCH_C:.c=.o) $(ARCH_S:.s=.o)
LIBK_OBJ:=$(LIBK_C:.c=.libk.o)

LIB_BINARIES:=libk.a
LIBS:=$(LIBS) -nostdlib -lk -lgcc

.PHONY: all
.PHONY: clean
.PHONY: install-headers
.PHONY: install-kernel
.PHONY: install-lib
.PHONY: tags
.PHONY: test

all: install-headers install-lib install-kernel os.iso

install-headers:
	for module in $(MODULES) ; do \
		mkdir -p $(SYSROOT)$(PREFIX)/include; \
		cp -r --preserve=timestamps $$module/include/* \
			$(SYSROOT)$(PREFIX)/include/ ; \
	done

install-kernel: os.kernel
	mkdir -p $(SYSROOT)/boot
	cp os.kernel $(SYSROOT)/boot/

install-lib: $(LIB_BINARIES)
	mkdir -p $(SYSROOT)$(PREFIX)/lib
	for lib in $(LIB_BINARIES) ; do \
		cp $$lib $(SYSROOT)$(PREFIX)/lib ; \
	done

clean:
	-rm $(KERNEL_OBJ) $(ARCH_OBJ) $(LIBK_OBJ)
	-rm os.kernel
	-rm os.iso
	-rm libk.a
	-rm -rf isodir
	-rm -rf sysroot
	-rm tags

tags:
	ctags -R --exclude=isodir .

test:

libk.a: $(LIBK_OBJ)
	$(AR) -rsc $@ $(LIBK_OBJ)

os.kernel: $(ARCHDIR)/linker.ld $(KERNEL_OBJ) $(ARCH_OBJ)
	$(CC) -T $< -o $@ $(CFLAGS) $(LDFLAGS) $(KERNEL_OBJ) $(ARCH_OBJ) $(LIBS)
	grub-file --is-x86-multiboot $@

os.iso: grub.cfg os.kernel
	mkdir -p isodir/boot/grub
	cp os.kernel isodir/boot/os.kernel
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o $@ isodir

%.o: %.s
	$(AS) $< -o $@

%.libk.o: %.c
	$(CC) -c $< -o $@ $(LIBK_CFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)


