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

C_SOURCES:=$(wildcard kernel/*.c $(ARCHDIR)/*.c)
LIBK_SOURCES:=$(wildcard libc/stdio/*.c libc/string/*.c)
ASM_SOURCES:=$(wildcard $(ARCHDIR)/*.s)
C_OBJ:=$(C_SOURCES:.c=.o)
ASM_OBJ:=$(ASM_SOURCES:.s=.o)
LIBK_OBJS:=$(LIBK_SOURCES:.c=.libk.o)

LIB_BINARIES:=libk.a
LIBS:=$(LIBS) -nostdlib -lk -lgcc

.PHONY: all
.PHONY: clean
.PHONY: install-headers
.PHONY: install-kernel
.PHONY: install-lib
.PHONY: tags

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
	-rm $(C_OBJ) $(ASM_OBJ)
	-rm os.kernel
	-rm os.iso
	-rm libk.a
	-rm -rf isodir
	-rm -rf sysroot
	-rm tags

tags:
	ctags -R --exclude=isodir .

libk.a: $(LIBK_OBJS)
	$(AR) -rsc $@ $(LIBK_OBJS)

os.kernel: $(ARCHDIR)/linker.ld $(C_OBJ) $(ASM_OBJ)
	$(CC) -T $< -o $@ $(CFLAGS) $(LDFLAGS) $(C_OBJ) $(ASM_OBJ) $(LIBS)
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


