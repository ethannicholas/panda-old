#!/bin/bash

echo "Building ui (native)..."

export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/../.."
source $BASEDIR/scripts/setup-script.sh
cd $BASEDIR

mkdir -p $NATIVE_TARGET/ui/lib
mkdir -p $SHARED_TARGET/ui/lib
rm -f $SHARED_TARGET/ui/lib/pandaui.plink
$PANDAC -f h -o $NATIVE_TARGET/ui/ui.h src/ui/panda/panda/ui/*.panda src/ui/panda/panda/ui/events/*.panda src/ui/panda/panda/ui/images/*.panda src/ui/panda/panda/gl/*.panda
$PANDAC -f lib -O -o $NATIVE_TARGET/ui/lib/pandaui.o src/ui/panda/panda/ui/*.panda src/ui/panda/panda/ui/events/*.panda src/ui/panda/panda/ui/images/*.panda src/ui/panda/panda/gl/*.panda
$PANDAC -f plink -o $SHARED_TARGET/ui/lib/pandaui.plink src/ui/panda/panda/ui/*.panda src/ui/panda/panda/ui/events/*.panda src/ui/panda/panda/ui/images/*.panda src/ui/panda/panda/gl/*.panda
if [ "$?" -ne "0" ]; then
    exit 1
fi

if [ $PLATFORM = "Darwin" ]; then
    SDL_INCLUDE=/opt/local/include/SDL2/
    SDL_IMAGE_INCLUDE=/opt/local/include/SDL2/
else
    SDL_INCLUDE=/usr/include/SDL2
    SDL_IMAGE_INCLUDE=/usr/include/SDL2
fi
gcc -c -g -I$SDL_INCLUDE -I$SDL_IMAGE_INCLUDE -Isrc/core/c -I/opt/local/include/cairo/ \
    -o $NATIVE_TARGET/ui/lib/ui.o -Isrc/ui/c -I$NATIVE_TARGET/ui \
    -I$NATIVE_TARGET/core/c $INCLUDES -fPIC\
    src/ui/c/ui.c
if [ "$?" -ne "0" ]; then
    exit 1
fi

if [ $PLATFORM = "Darwin" ]; then
    libtool -undefined suppress -flat_namespace -dynamic $NATIVE_TARGET/ui/lib/pandaui.o \
    $NATIVE_TARGET/ui/lib/ui.o -o $NATIVE_TARGET/ui/lib/libpandaui.dylib
else
    gcc -shared -o $NATIVE_TARGET/ui/lib/libpandaui.so $NATIVE_TARGET/ui/lib/pandaui.o \
    $NATIVE_TARGET/ui/lib/ui.o
fi

