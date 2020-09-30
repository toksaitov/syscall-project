#!/usr/bin/env sh

export PATH=$PATH:`cd ../../qemu; pwd`

DISPLAY=`[ "$OSTYPE" == "msys" ] && echo "-display gtk" || echo "-nographic"`

qemu-system-mips64el                            \
    -machine malta                              \
    -cpu 5KEc                                   \
    -m 1024M                                    \
    -smp 1                                      \
    $DISPLAY                                    \
    -drive file=debian-10.5.0-mips64el-hd.qcow2 \
    -device e1000,netdev=net                    \
    -netdev user,id=net,hostfwd=tcp::2222-:22   \
    -kernel kernel -initrd initrd               \
    -append "root=LABEL=rootfs console=ttyS0"