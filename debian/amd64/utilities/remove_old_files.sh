#!/usr/bin/env sh

DISK_IMAGE='debian-10.6.0-amd64-hd.qcow2'
EFI_FIRMWARE='OVMF_CODE-pure-efi.fd'
EFI_VARS='OVMF_VARS-pure-efi.fd'

rm -i "$DISK_IMAGE".old   \
      "$EFI_FIRMWARE".old \
      "$EFI_VARS".old
