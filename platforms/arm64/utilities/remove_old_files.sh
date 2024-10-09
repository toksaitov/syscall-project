#!/usr/bin/env sh

DISK_IMAGE='debian-12.7.0-arm64-hd.qcow2'
EFI_FIRMWARE_CODE='AAVMF_CODE.fd'
EFI_FIRMWARE_VARS='AAVMF_VARS.fd'
LINUX_KERNEL='vmlinuz'
LINUX_RAMDISK='initrd.gz'

rm -i "$DISK_IMAGE".old        \
      "$EFI_FIRMWARE_CODE".old \
      "$EFI_FIRMWARE_VARS".old \
      "$LINUX_KERNEL".old      \
      "$LINUX_RAMDISK".old
