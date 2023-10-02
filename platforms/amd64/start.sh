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

qemu-system-x86_64                                               \
    $DISP                                                        \
    -machine type=pc,accel=tcg                                   \
    -m 1024M                                                     \
    -smp 1                                                       \
    -drive if=pflash,file=OVMF_CODE_4M.fd,format=raw,readonly=on \
    -drive if=pflash,file=OVMF_VARS_4M.fd,format=raw             \
    -drive if=virtio,file=debian-12.1.0-amd64-hd.qcow2           \
    -nic user,model=virtio-net-pci,hostfwd=tcp::2222-:22
