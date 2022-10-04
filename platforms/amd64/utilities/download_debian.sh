#!/usr/bin/env sh

DEBIAN='debian-11.5.0-amd64-netinst.iso'
URL="https://www.dropbox.com/s/bkl6t13zprli6ic/$DEBIAN?dl=1/"

curl --location -C - --output "$DEBIAN" "$URL"
