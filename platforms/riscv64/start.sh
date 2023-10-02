#!/usr/bin/env sh

SCRIPT_LOC=`dirname "$BASH_SOURCE"`
export PATH=$PATH:`cd "$SCRIPT_LOC/../../qemu" > /dev/null 2>&1; pwd`

case $OSTYPE in
    darwin*)
        DISP='-display cocoa';;
    msys*)
        DISP='-display gtk';;
    *)
        DISP='-nographic -serial mon:stdio -device virtio-serial-pci';;
esac

qemu-system-riscv64                                          \
    $DISP                                                    \
    -machine virt                                            \
    -cpu rv64                                                \
    -m 1024M                                                 \
    -smp 1                                                   \
    -bios fw_jump.elf                                        \
    -kernel uboot.elf                                        \
    -append "root=LABEL=rootfs console=ttyS0"                \
    -device virtio-blk-device,drive=hd                       \
    -drive file=debian-12.1.0-riscv64-hd.qcow2,if=none,id=hd \
    -device virtio-net-device,netdev=net                     \
    -netdev user,id=net,hostfwd=tcp::2222-:22                \
    -object rng-random,filename=/dev/urandom,id=rng          \
    -device virtio-rng-device,rng=rng
