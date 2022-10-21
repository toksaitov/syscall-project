#!/usr/bin/env sh

export PATH=$PATH:`cd ../../qemu > /dev/null 2>&1; pwd`

case $OSTYPE in
    darwin*)
        DISP='-display cocoa';;
    msys*)
        DISP='-display gtk';;
    *)
        DISP='-nographic -serial mon:stdio -device virtio-serial-pci';;
esac

qemu-system-aarch64                                                                                  \
    $DISP                                                                                            \
    -machine type=virt,accel=tcg                                                                     \
    -cpu cortex-a57                                                                                  \
    -m 1024M                                                                                         \
    -smp 1                                                                                           \
    -kernel vmlinuz                                                                                  \
    -append 'console=ttyS0 DEBIAN_FRONTEND=newt TERM=ansi'                                           \
    -initrd initrd.gz                                                                                \
    -drive if=pflash,file=AAVMF_CODE.fd,format=raw                                                   \
    -drive if=pflash,file=AAVMF_VARS.fd,format=raw                                                   \
    -drive if=virtio,file=debian-11.5.0-arm64-hd.qcow2                                               \
    -drive if=none,file=debian-11.5.0-arm64-netinst.iso,media=cdrom,format=raw,readonly=on,id=cdrom0 \
    -device virtio-scsi-pci,id=scsi0                                                                 \
    -device scsi-cd,bus=scsi0.0,drive=cdrom0                                                         \
    -nic user,model=virtio-net-pci,hostfwd=tcp::2222-:22
