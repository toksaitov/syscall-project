#!/usr/bin/env sh

DEBIAN='debian-12.7.0-arm64-netinst.iso'
URL="https://www.dropbox.com/scl/fi/y2w11601r1gcnwz56q5q6/$DEBIAN?rlkey=ncomep6gen1b5u21yatb4i91a&dl=1"

curl --location -C - --output "$DEBIAN" "$URL"
