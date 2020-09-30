#!/usr/bin/env sh

export PATH=$PATH:`cd ../../qemu; pwd`

DISPLAY=`[ "$OSTYPE" == "msys" ] && echo "-display gtk" || echo "-nographic"`

qemu-system-x86_64                                                  \
    -machine type=pc,accel=tcg                                      \
    -m 1024M                                                        \
    -smp 1                                                          \
    $DISPLAY                                                        \
    -drive if=pflash,file=OVMF_CODE-pure-efi.fd,format=raw,readonly \
    -drive if=pflash,file=OVMF_VARS-pure-efi.fd,format=raw,readonly \
    -drive if=virtio,file=debian-10.6.0-amd64-hd.qcow2              \
    -nic user,model=virtio-net-pci,hostfwd=tcp::2222-:22            \
    -loadvm last
