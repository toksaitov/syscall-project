#!/usr/bin/env sh

DEBIAN='debian-12.1.0-amd64-netinst.iso'
URL="https://www.dropbox.com/scl/fi/ruwue34se4gml0xpi0g09/$DEBIAN?rlkey=olpioeiognfacqk7z7xpxpx1x&dl=1"

curl --location -C - --output "$DEBIAN" "$URL"
