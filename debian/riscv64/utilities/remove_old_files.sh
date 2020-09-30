#!/usr/bin/env sh

DISK_IMAGE='debian-10.5.0-riscv64-hd.qcow2'
KERNEL='kernel'
RAM_DISK='initrd'
BIOS='fw_jump.elf'
BOOTLOADER='uboot.elf'

rm -i "$DISK_IMAGE".old \
      "$KERNEL".old     \
      "$RAM_DISK".old   \
      "$BIOS".old       \
      "$BOOTLOADER".old
