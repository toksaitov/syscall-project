#!/usr/bin/env sh

QEMU_ARCHIVE='qemu-5.1.0-win32.tar.gz'
QEMU_DIRECTORY='qemu'
URL="https://www.dropbox.com/s/mcia2pjh3r6blt0/$QEMU_ARCHIVE?dl=1/"

curl --location -C - --output "$QEMU_ARCHIVE" "$URL"

test -e "$QEMU_DIRECTORY" && mv "$QEMU_DIRECTORY" "$QEMU_DIRECTORY"_old
mkdir "$QEMU_DIRECTORY" && tar -xvzf "$QEMU_ARCHIVE" -C "$QEMU_DIRECTORY" --strip-components 1
