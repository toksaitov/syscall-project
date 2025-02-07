#!/usr/bin/env sh

SCRIPT_LOC=`dirname "$BASH_SOURCE"`
export PATH=$PATH:`cd "$SCRIPT_LOC/../../qemu" > /dev/null 2>&1; pwd`

case $OSTYPE in
    darwin*)
        DISP='-display cocoa'
        TRM='ansi'
        ;;
    msys*)
        DISP='-display gtk'
        TRM='ansi'
        ;;
    *)
        DISP='-nographic -serial mon:stdio -device virtio-serial-pci'
        TRM='vt102'
        ;;
esac

qemu-system-x86_64                                                                                   \
    $DISP                                                                                            \
    -machine type=pc,accel=tcg                                                                       \
    -m 1024M                                                                                         \
    -smp 1                                                                                           \
    -kernel vmlinuz                                                                                  \
    -append "console=ttyS0 DEBIAN_FRONTEND=newt TERM=$TRM"                                           \
    -initrd initrd.gz                                                                                \
    -drive if=pflash,file=OVMF_CODE_4M.fd,format=raw                                                 \
    -drive if=pflash,file=OVMF_VARS_4M.fd,format=raw                                                 \
    -drive if=virtio,file=debian-12.7.0-amd64-hd.qcow2                                               \
    -drive if=none,file=debian-12.7.0-amd64-netinst.iso,media=cdrom,format=raw,readonly=on,id=cdrom0 \
    -device virtio-scsi-pci,id=scsi0                                                                 \
    -device scsi-cd,bus=scsi0.0,drive=cdrom0                                                         \
    -nic user,model=virtio-net-pci,hostfwd=tcp::2222-:22
