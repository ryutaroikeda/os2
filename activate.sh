#!/bin/bash

# path to cross compiler tools
CROSS_PATH="${HOME}/opt/cross/bin"
PATH="${CROSS_PATH}:${PATH}"

export HOST="i686-elf"
export ARCH="i386"
export AR="${HOST}-ar"
export AS="${HOST}-as"
export CC="${HOST}-gcc"

export SYSROOT="$(pwd)/sysroot"
CC="${CC} --sysroot=${SYSROOT}"

# assume we configured the cross compiler with --without-headers
CC="${CC} -isystem=/usr/include"

alias objdump="${CROSS_PATH}/${HOST}-objdump"
alias qemu="qemu-system-${ARCH}"
