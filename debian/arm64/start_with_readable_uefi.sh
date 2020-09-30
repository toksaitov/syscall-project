#!/usr/bin/env sh

export PATH=$PATH:`cd ../../qemu > /dev/null 2>&1; pwd`

DISP="-display gtk"
case $OSTYPE in darwin*)
    DISP="-display cocoa"
esac

qemu-system-aarch64                                                    \
    -machine virt                                                      \
    -cpu cortex-a57                                                    \
    -m 1024M                                                           \
    -smp 1                                                             \
    $DISP                                                              \
    -drive if=pflash,file=QEMU_EFI-pflash.raw,format=raw,readonly      \
    -drive if=pflash,file=vars-template-pflash.raw,format=raw,readonly \
    -drive if=virtio,file=debian-10.6.0-arm64-hd.qcow2                 \
    -nic user,model=virtio-net-pci,hostfwd=tcp::2222-:22
