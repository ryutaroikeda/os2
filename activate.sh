#!/bin/bash

# path to cross compiler tools
PATH="${HOME}/opt/cross/bin:${PATH}"

export HOST="i686-elf"
export ARCH="i386"
export AR="${HOST}-ar"
export AS="${HOST}-as"
export CC="${HOST}-gcc"

export CFLAGS="${CFLAGS} -Wextra -Wall -pedantic -Werror -Wshadow \
	-Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes \
	-Wconversion"

export SYSROOT="$(pwd)/sysroot"
CC="${CC} --sysroot=${SYSROOT}"

# assume we configured the cross compiler with --without-headers
CC="${CC} -isystem=/usr/include"

