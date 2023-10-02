#!/usr/bin/env sh

OS_ARCHIVE='debian-12.1.0-riscv64.tar.gz'
DISK_IMAGE='debian-12.1.0-riscv64-hd.qcow2'
KERNEL='kernel'
RAM_DISK='initrd'
BIOS='fw_jump.elf'
BOOTLOADER='uboot.elf'

URL="https://www.dropbox.com/scl/fi/b4ib3i2ul2gy9q4rm0hse/$OS_ARCHIVE?rlkey=gb8mozw5479tf7y7ekh1htktq&dl=1"
curl --location -C - --output "$OS_ARCHIVE" "$URL"

test -e "$DISK_IMAGE" && mv "$DISK_IMAGE" "$DISK_IMAGE".old
test -e "$KERNEL" && mv "$KERNEL" "$KERNEL".old
test -e "$RAM_DISK" && mv "$RAM_DISK" "$RAM_DISK".old
test -e "$BIOS" && mv "$BIOS" "$BIOS".old
test -e "$BOOTLOADER" && mv "$BOOTLOADER" "$BOOTLOADER".old
tar -xvzf "$OS_ARCHIVE"
