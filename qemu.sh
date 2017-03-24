#!/bin/bash

set -o errexit
set -o nounset

qemu-system-${ARCH} -cdrom os.iso

