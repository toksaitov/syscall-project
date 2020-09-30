#!/usr/bin/env sh

export PATH=$PATH:`cd ../../qemu > /dev/null 2>&1; pwd`

DISP="-display gtk"
case $OSTYPE in darwin*)
    DISP="-display cocoa"
esac

qemu-system-x86_64                                                  \
    -machine type=pc,accel=tcg                                      \
    -m 1024M                                                        \
    -smp 1                                                          \
    $DISP                                                           \
    -drive if=pflash,file=OVMF_CODE-pure-efi.fd,format=raw,readonly \
    -drive if=pflash,file=OVMF_VARS-pure-efi.fd,format=raw,readonly \
    -drive if=virtio,file=debian-10.6.0-amd64-hd.qcow2              \
    -nic user,model=virtio-net-pci,hostfwd=tcp::2222-:22            \
    -loadvm last
