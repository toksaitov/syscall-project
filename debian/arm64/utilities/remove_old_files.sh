#!/usr/bin/env sh

DISK_IMAGE='debian-10.6.0-arm64-hd.qcow2'
EFI_FIRMWARE='QEMU_EFI-pflash.raw'
EFI_VARS='vars-template-pflash.raw'

rm -i "$DISK_IMAGE".old   \
      "$EFI_FIRMWARE".old \
      "$EFI_VARS".old
