#!/usr/bin/env sh

export PATH=$PATH:`cd ../../qemu; pwd`

DISPLAY=`[ "$OSTYPE" == "msys" ] && echo "-display gtk" || echo "-nographic"`

qemu-system-x86_64                                                                                \
    -machine type=pc,accel=tcg                                                                    \
    -m 1024M                                                                                      \
    -smp 1                                                                                        \
    $DISPLAY                                                                                      \
    -drive if=pflash,file=OVMF_CODE-pure-efi.fd,format=raw                                        \
    -drive if=pflash,file=OVMF_VARS-pure-efi.fd,format=raw                                        \
    -drive if=virtio,file=debian-10.6.0-amd64-hd.qcow2                                            \
    -drive if=none,file=debian-10.6.0-amd64-netinst.iso,media=cdrom,format=raw,readonly,id=cdrom0 \
    -device virtio-scsi-pci,id=scsi0                                                              \
    -device scsi-cd,bus=scsi0.0,drive=cdrom0                                                      \
    -nic user,model=virtio-net-pci,hostfwd=tcp::2222-:22