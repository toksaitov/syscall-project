#!/usr/bin/env sh

export PATH=$PATH:`cd ../../qemu > /dev/null 2>&1; pwd`

DISPLAY="-display gtk"
case $OSTYPE in darwin*)
    DISPLAY="-display cocoa"
esac

qemu-system-riscv64                                          \
    -machine virt                                            \
    -cpu rv64                                                \
    -m 1024M                                                 \
    -smp 1                                                   \
    $DISPLAY                                                 \
    -bios fw_jump.elf                                        \
    -kernel uboot.elf                                        \
    -device virtio-blk-device,drive=hd                       \
    -drive file=debian-10.5.0-riscv64-hd.qcow2,if=none,id=hd \
    -device virtio-net-device,netdev=net                     \
    -netdev user,id=net,hostfwd=tcp::2223-:22                \
    -object rng-builtin,id=rng                               \
    -append "root=LABEL=rootfs console=ttyS0"
