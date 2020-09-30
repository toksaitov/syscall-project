#!/usr/bin/env sh

export PATH=$PATH:`cd ../../qemu > /dev/null 2>&1 || cd ../../../qemu > /dev/null 2>&1; pwd` 

DISK='debian-10.6.0-arm64-hd.qcow2'

test -e "$DISK" && mv "$DISK" "$DISK".old
qemu-img convert -O qcow2 -c "$DISK".old "$DISK"
