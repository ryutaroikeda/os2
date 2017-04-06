# os2

Based on wiki.osdev.org

## Building the cross-compiler

Install the following on a Unix-like environment
- gcc
- make
- bison
- flex
- libgmp3-dev
- libmpfr-dev
- libmpc-dev
- libisl-dev (optional)
- libcloog-isl-dev (optional)
- texinfo

Download the source for gcc and binutils into $HOME/build

To build,
```bash
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
# needed when compiling gcc
export PATH="$PREFIX/bin:$PATH"

# build binutils
cd "$HOME/build"
mkdir build-binutils
cd build-binutils
../binutils-2.28.0/configure --target=$TARGET --prefix="$PREFIX" \
	--with-sysroot --disable-nls --disable-werror
make
make install

# build the cross-compiling gcc
cd "$HOME/build"
mkdir build-gcc
cd build-gcc
../gcc-6.3.0/configure --target=$TARGET --prefix="$PREFIX" \
	--disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
```

This has been tested with gcc 6.3.0 and binutils 2.28.

## Build on linux

Build and install an i686 cross-compiler at `$HOME/opt/cross/bin`.

`cd os2`

Then run

`source activate.sh`

To build the image,

`make os.kernel`.

This requires the packages `grub-mkrescue` and `xorriso`.
`grub-mkrescue` fails silently if you don't have `xorriso` installed.

To run with QEMU, do

`qemu-system-i386 -cdrom os.kernel`

If the boot fails with something like `Could not read from CD-ROM (code 0009)`
you may need to `apt-get install grub-pc-bin`.

## to do

- global constructors
- paging

interrupts
- macro to generate 255 * 2 handlers for error code and none error code. 
just a piece of assembly to push irq and dummy error code if needed, then call
common interrupt handler.
- register interrupt handler by giving irq, error code flag, and c function to
call; this gets stored in a separate table (interrupt handler table). Update
actual idt with pointer to appropriate assembly based on error code flag.
- common interrupt handler prepares interrupt stack, then use irq to get
  function from interrupt handler table. Call it, then iret.

Using `__attribute__((packed))` can be dangerous on hardware that doesn't
support access to unaligned, but it's okay on x86 systems.


