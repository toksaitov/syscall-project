#!/usr/bin/env sh

OS_ARCHIVE='debian-12.1.0-riscv64.tar.gz'
DISK_IMAGE='debian-12.1.0-riscv64-hd.qcow2'
KERNEL='kernel'
RAM_DISK='initrd'
BIOS='fw_jump.elf'
BOOTLOADER='uboot.elf'

URL="https://www.dropbox.com/s/cr6kx1khy8354ypf6yhfv/$OS_ARCHIVE?dl=1/"

curl --location -C - --output "$OS_ARCHIVE" "$URL"

test -e "$DISK_IMAGE" && mv "$DISK_IMAGE" "$DISK_IMAGE".old
test -e "$KERNEL" && mv "$KERNEL" "$KERNEL".old
test -e "$RAM_DISK" && mv "$RAM_DISK" "$RAM_DISK".old
test -e "$BIOS" && mv "$BIOS" "$BIOS".old
test -e "$BOOTLOADER" && mv "$BOOTLOADER" "$BOOTLOADER".old
tar -xvzf "$OS_ARCHIVE"
