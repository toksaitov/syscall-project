#!/usr/bin/env sh

DISK_IMAGE='debian-12.1.0-amd64-hd.qcow2'
EFI_FIRMWARE='OVMF.fd'
LINUX_KERNEL='vmlinuz'
LINUX_RAMDISK='initrd.gz'

rm -i "$DISK_IMAGE".old    \
      "$EFI_FIRMWARE".old  \
      "$LINUX_KERNEL".old  \
      "$LINUX_RAMDISK".old
