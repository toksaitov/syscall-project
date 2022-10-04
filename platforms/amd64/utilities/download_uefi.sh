#!/usr/bin/env sh

EFI_ARCHIVE='edk2-ovmf-20200919.1456-x64.tar.gz'
EFI_FIRMWARE='OVMF_CODE-pure-efi.fd'
EFI_VARS='OVMF_VARS-pure-efi.fd'

URL="https://www.dropbox.com/s/ll4wv684csg2af8/$EFI_ARCHIVE?dl=1/"

curl --location -C - --output "$EFI_ARCHIVE" "$URL"

test -e "$EFI_FIRMWARE" && mv "$EFI_FIRMWARE" "$EFI_FIRMWARE".old
test -e "$EFI_VARS" && mv "$EFI_VARS" "$EFI_VARS".old
tar -xvzf "$EFI_ARCHIVE"
