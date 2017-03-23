#!/bin/bash

# path to cross compiler tools
PATH="${HOME}/opt/cross/bin:${PATH}"

export HOST="i686-elf"
export AR="${HOST}-ar"
export AS="${HOST}-as"
export CC="${HOST}-gcc"

export SYSROOT="$(pwd)/sysroot"

# assume we configured the cross compiler with --without-headers
export CC="${CC} -isystem ${SYSROOT}/usr/include"

