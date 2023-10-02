#!/usr/bin/env sh

DEBIAN='debian-12.1.0-arm64-netinst.iso'
URL="https://www.dropbox.com/s/s7b15er54wm1ocnb3m3yw/$DEBIAN?dl=1"

curl --location -C - --output "$DEBIAN" "$URL"
