#!/usr/bin/env sh

DEBIAN='debian-10.6.0-amd64-netinst.iso'
URL="https://www.dropbox.com/s/qibwvrnvfcpq2gu/$DEBIAN?dl=1/"

curl --location -C - --output "$DEBIAN" "$URL"
