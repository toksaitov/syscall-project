#!/usr/bin/env sh

DEBIAN='debian-11.1.0-arm64-netinst.iso'
URL="https://www.dropbox.com/s/tyqqa197e1ybky7/$DEBIAN?dl=1/"

curl --location -C - --output "$DEBIAN" "$URL"
