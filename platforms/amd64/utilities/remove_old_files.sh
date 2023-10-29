#!/usr/bin/env sh

DISK_IMAGE='debian-12.1.0-amd64-hd.qcow2'
EFI_FIRMWARE_CODE='OVMF_CODE_4M.fd'
EFI_FIRMWARE_VARS='OVMF_VARS_4M.fd'
LINUX_KERNEL='vmlinuz'
LINUX_RAMDISK='initrd.gz'

rm -i "$DISK_IMAGE".old        \
      "$EFI_FIRMWARE_CODE".old \
      "$EFI_FIRMWARE_VARS".old \
      "$LINUX_KERNEL".old      \
      "$LINUX_RAMDISK".old
