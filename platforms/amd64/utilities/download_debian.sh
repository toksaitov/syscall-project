#!/usr/bin/env sh

DEBIAN='debian-12.7.0-amd64-netinst.iso'
URL="https://www.dropbox.com/scl/fi/0gp217wh3qtsa9azzif3n/$DEBIAN?rlkey=2yqmca06cwd0v1xdoz5krazs7&dl=1"

curl --location -C - --output "$DEBIAN" "$URL"
