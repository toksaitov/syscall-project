#!/usr/bin/env sh

DEBIAN='debian-12.1.0-arm64-netinst.iso'
URL="https://www.dropbox.com/scl/fi/s7b15er54wm1ocnb3m3yw/$DEBIAN?rlkey=wglf0352hgxyhxs3p0opgfntm&dl=1"

curl --location -C - --output "$DEBIAN" "$URL"
