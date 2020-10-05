#!/usr/bin/env sh

export PATH=$PATH:`cd ../../qemu > /dev/null 2>&1; pwd`

DISP="-display gtk"
case $OSTYPE in darwin*)
    DISP="-display cocoa"
esac

qemu-system-mips64el                            \
    -machine malta                              \
    -cpu 5KEc                                   \
    -m 1024M                                    \
    -smp 1                                      \
    $DISP                                       \
    -drive file=debian-10.5.0-mips64el-hd.qcow2 \
    -device e1000,netdev=net                    \
    -netdev user,id=net,hostfwd=tcp::2222-:22   \
    -kernel kernel -initrd initrd               \
    -append "root=LABEL=rootfs console=ttyS0"
