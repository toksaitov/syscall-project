#!/usr/bin/env sh

FIRMWARE_ARCHIVE='firmware-x64.tar.gz'
EFI_FIRMWARE='OVMF.fd'
LINUX_KERNEL='vmlinuz'
LINUX_RAMDISK='initrd.gz'

URL="https://www.dropbox.com/s/ugwooh54h8d47zox9sjty/$FIRMWARE_ARCHIVE?dl=1/"

curl --location -C - --output "$FIRMWARE_ARCHIVE" "$URL"

test -e "$EFI_FIRMWARE"  && mv "$EFI_FIRMWARE"  "$EFI_FIRMWARE".old
test -e "$LINUX_KERNEL"  && mv "$LINUX_KERNEL"  "$LINUX_KERNEL".old
test -e "$LINUX_RAMDISK" && mv "$LINUX_RAMDISK" "$LINUX_RAMDISK".old
tar -xvzf "$FIRMWARE_ARCHIVE"
