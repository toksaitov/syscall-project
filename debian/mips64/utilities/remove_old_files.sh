#!/usr/bin/env sh

DISK_IMAGE='debian-10.5.0-mips64el-hd.qcow2'
KERNEL='kernel'
RAM_DISK='initrd'

rm -i "$DISK_IMAGE".old \
      "$KERNEL".old     \
      "$RAM_DISK".old
