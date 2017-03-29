MODULES:=libc kernel

CFLAGS?=-O2 -g
SYSROOT?=
PREFIX?=/usr
LDFLAGS?=
LIBS?=

CFLAGS:=$(CFLAGS) -Wextra -Wall -pedantic -Werror -Wshadow -Wpointer-arith \
	-Wcast-qual -Wstrict-prototypes -Wmissing-prototypes -Wconversion \
	-ffreestanding -std=gnu99 -fstack-protector-all -Ikernel/include

LIBK_CFLAGS:=$(CFLAGS) -D__is_libk

ARCH?=i386
ARCHDIR:=arch/$(ARCH)

KERNEL_C:=$(wildcard kernel/*.c)
ARCH_C:=$(wildcard $(ARCHDIR)/*.c)
ARCH_S:=$(wildcard $(ARCHDIR)/*.s)
LIBK_C:=$(wildcard libc/stdio/*.c libc/string/*.c libc/stdlib/*.c)

KERNEL_OBJ:=$(KERNEL_C:.c=.o)
ARCH_OBJ:=$(ARCH_C:.c=.o) $(ARCH_S:.s=.s.o)
LIBK_OBJ:=$(LIBK_C:.c=.libk.o)

LIB_BINARIES:=libk.a
LIBS:=$(LIBS) -nostdlib -lk -lgcc

.PHONY: all
.PHONY: clean
.PHONY: tags

all: install-headers os.iso

clean:
	-rm $(KERNEL_OBJ) $(ARCH_OBJ) $(LIBK_OBJ)
	-rm os.kernel
	-rm os.iso
	-rm libk.a
	-rm -rf isodir
	-rm -rf sysroot
	-rm tags

tags:
	ctags -R --exclude=isodir --exclude=sysroot .

install-headers:
	mkdir -p $(SYSROOT)$(PREFIX)/include
	for module in $(MODULES) ; do \
		cp -r --preserve=timestamps $$module/include/* \
			$(SYSROOT)$(PREFIX)/include/ ; \
	done

os.kernel: $(ARCHDIR)/linker.ld $(KERNEL_OBJ) $(ARCH_OBJ) $(LIB_BINARIES)
	mkdir -p $(SYSROOT)$(PREFIX)/lib
	for lib in $(LIB_BINARIES) ; do \
		cp --preserve=timestamps $$lib $(SYSROOT)$(PREFIX)/lib ; \
	done
	$(CC) -T $< -o $@ $(CFLAGS) $(LDFLAGS) $(KERNEL_OBJ) $(ARCH_OBJ) $(LIBS)
	grub-file --is-x86-multiboot $@
	mkdir -p $(SYSROOT)/boot
	cp --preserve=timestamps os.kernel $(SYSROOT)/boot/

os.iso: grub.cfg os.kernel
	mkdir -p isodir/boot/grub
	cp $(SYSROOT)/boot/os.kernel isodir/boot/os.kernel
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o $@ isodir

libk.a: $(LIBK_OBJ)
	$(AR) -rsc $@ $(LIBK_OBJ)

# will be used for userspace
libssp.a:
	$(AR) -rsc $@

# will be used for userspace
libssp_nonshared.a:
	$(AR) -rsc $@

%.s.o: %.s
	$(AS) $< -o $@

%.libk.o: %.c
	$(CC) -MD -c $< -o $@ $(LIBK_CFLAGS)

%.o: %.c
	$(CC) -MD -c $< -o $@ $(CFLAGS)

-include $(KERNEL_OBJ:.o=.d) $(ARCH_OBJ:.o=.d) $(LIBK_OBJ:.o=.d)

