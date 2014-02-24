#!/bin/bash

echo "Building GL (native)..."

export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/../.."
source $BASEDIR/scripts/setup-script.sh
cd $BASEDIR

mkdir -p $NATIVE_TARGET/gl/lib
rm -f $NATIVE_TARGET/gl/lib/pandagl.plink # FIXME: leaving this around causes a build error due to the idiotic way I look fields and methods up on pass 2
$PANDAC -f h -o $NATIVE_TARGET/gl/gl.h src/gl/panda/panda/gl/*.panda src/gl/panda/panda/gl/events/*.panda src/gl/panda/panda/gl/images/*.panda src/gl/panda/panda/gl/shapes/*.panda
$PANDAC -f lib -o $NATIVE_TARGET/gl/lib/pandagl.o src/gl/panda/panda/gl/*.panda src/gl/panda/panda/gl/events/*.panda src/gl/panda/panda/gl/images/*.panda src/gl/panda/panda/gl/shapes/*.panda
if [ "$?" -ne "0" ]; then
    exit 1
fi

if [ $PLATFORM = "Darwin" ]; then
    SDL_INCLUDE=/Library/Frameworks/SDL2.framework/Headers/
    SDL_IMAGE_INCLUDE=/Library/Frameworks/SDL2_image.framework/Headers/
else
    SDL_INCLUDE=/usr/include/SDL2
    SDL_IMAGE_INCLUDE=/usr/include/SDL2
fi
gcc -c -g -I$SDL_INCLUDE -I$SDL_IMAGE_INCLUDE -Isrc/core/c -I/opt/local/include/cairo/ \
    -o $NATIVE_TARGET/gl/lib/gl.o -Isrc/gl/c -I$NATIVE_TARGET/gl \
    -I$NATIVE_TARGET/core/c $INCLUDES -fPIC\
    src/gl/c/gl.c
if [ "$?" -ne "0" ]; then
    exit 1
fi

if [ $PLATFORM = "Darwin" ]; then
    libtool -undefined suppress -flat_namespace -dynamic $NATIVE_TARGET/gl/lib/pandagl.o \
    $NATIVE_TARGET/gl/lib/gl.o -o $NATIVE_TARGET/gl/lib/libpandagl.dylib
else
    gcc -shared -o $NATIVE_TARGET/gl/lib/libpandagl.so $NATIVE_TARGET/gl/lib/pandagl.o \
    $NATIVE_TARGET/gl/lib/gl.o
fi

