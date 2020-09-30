#!/usr/bin/env sh

OS_ARCHIVE='debian-10.5.0-mips64el.tar.gz'
DISK_IMAGE='debian-10.5.0-mips64el-hd.qcow2'
KERNEL='kernel'
RAM_DISK='initrd'

URL="https://www.dropbox.com/s/8ndw5ob8a5a56m1/$OS_ARCHIVE?dl=1/"

curl --location -C - --output "$OS_ARCHIVE" "$URL"

test -e "$DISK_IMAGE" && mv "$DISK_IMAGE" "$DISK_IMAGE".old
test -e "$KERNEL" && mv "$KERNEL" "$KERNEL".old
test -e "$RAM_DISK" && mv "$RAM_DISK" "$RAM_DISK".old
tar -xvzf "$OS_ARCHIVE"
