#!/usr/bin/env sh

EFI_ARCHIVE='edk2-ovmf-20200919.1456-aarch64.tar.gz'
EFI_FIRMWARE='QEMU_EFI-pflash.raw'
EFI_VARS='vars-template-pflash.raw'

URL="https://www.dropbox.com/s/5jqesshom6820dn/$EFI_ARCHIVE?dl=1/"

curl --location -C - --output "$EFI_ARCHIVE" "$URL"

test -e "$EFI_FIRMWARE" && mv "$EFI_FIRMWARE" "$EFI_FIRMWARE".old
test -e "$EFI_VARS" && mv "$EFI_VARS" "$EFI_VARS".old
tar -xvzf "$EFI_ARCHIVE"
