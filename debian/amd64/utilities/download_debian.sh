#!/usr/bin/env sh

DEBIAN='debian-11.1.0-amd64-netinst.iso'
URL="https://www.dropbox.com/s/m32vcf5mn8m5gdp/$DEBIAN?dl=1/"

curl --location -C - --output "$DEBIAN" "$URL"
