#!/usr/bin/env sh

DEBIAN='debian-10.6.0-arm64-netinst.iso'
URL="https://www.dropbox.com/s/moah26srezpdv91/$DEBIAN?dl=1/"

curl --location -C - --output "$DEBIAN" "$URL"
