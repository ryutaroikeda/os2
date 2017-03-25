# os2

Based on wiki.osdev.org

## Build on linux

Build and install an i686 cross-compiler at `$HOME/opt/cross/bin`.

`cd os2`

Then run

`source activate.sh`

To build the image,

`make os.kernel`.

This requires `grub-mkrescue` and `xorriso`.
`grub-mkrescue` fails silently if you don't have `xorriso` installed.

To run with QEMU, do

`qemu-system-i386 -cdrom os.kernel`

If the boot fails with something like `Could not read from CD-ROM (code 0009)`
you may need to `apt-get install grub-pc-bin`.

## to do

- abort
- panic
- stack smashing protection
- global constructor
- userland
- unit tests

