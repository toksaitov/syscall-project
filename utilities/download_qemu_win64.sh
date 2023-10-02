#!/usr/bin/env sh

QEMU_ARCHIVE='qemu-8.1.0-win64.tar.gz'
QEMU_DIRECTORY='qemu'
URL="https://www.dropbox.com/scl/fi/9vk9mn5glqcwtwk2km4j0/$QEMU_ARCHIVE?rlkey=0fcw26bsmurh0cbu6fp3p7giv&dl=1"
curl --location -C - --output "$QEMU_ARCHIVE" "$URL"

test -e "$QEMU_DIRECTORY" && mv "$QEMU_DIRECTORY" "$QEMU_DIRECTORY"_old
mkdir "$QEMU_DIRECTORY" && tar -xvzf "$QEMU_ARCHIVE" -C "$QEMU_DIRECTORY" --strip-components 1
