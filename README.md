# os2

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

- higher half kernel and paging
- global constructors


## structure

- arch
	- i386
		- don't expose headers

- kernel
	- include
		- .h implemented by arch or in kernel, exposed to libk
	- arch independent .c

- libc and libk

