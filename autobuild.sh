#!/bin/sh

set -e

BUILDDIR="./build/"
EXE="./battaglia_navale"
CMAKEFILEPATH=".."

if [ ! -d "$BUILDDIR" ]; then
    mkdir -p "$BUILDDIR"
fi

cd "$BUILDDIR"
cmake "$CMAKEFILEPATH"
make
if [ ! "$@" ]; then
    "$EXE"
else 
    "$EXE" "$@"
fi
cd "$CMAKEFILEPATH"
