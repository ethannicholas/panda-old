#!/bin/bash

# "phase 1" of the build is performed using the bootstrap compiler, and 
# "phase 2" is performed using first the generated Java compiler and then the 
# generated native compiler. Being able to run these two phases separately can
# make incompatible changes easier.

export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/.."
cd $BASEDIR
source scripts/setup-script.sh

export PANDA_HOME="$TARGET"
export PANDAC="java -ea -Xmx2g -jar $JAVA_TARGET/pandac/bin/pandac.jar -L $NATIVE_TARGET/core/lib $@"
export PANDA_HOME="$TARGET"

CORE_FILES="src/core/panda/panda/core/*.panda\
        src/core/panda/panda/collections/*.panda src/core/panda/panda/threads/*.panda\
        src/core/panda/panda/io/*.panda src/core/panda/panda/math/*.panda"
STATIC_SETTINGS="$SHARED_TARGET/StaticSettings.panda"





echo DEBUG CLEANUPS
$PANDAC -XnoCoreLib -f plink -o $SHARED_TARGET/core/lib/PandaCoreClasses.plink $CORE_FILES
STATIC_SETTINGS=$SHARED_TARGET/StaticSettings.panda
echo "package org.pandalanguage.pandac.compiler" > "$STATIC_SETTINGS"
echo "class StaticSettings {" >> "$STATIC_SETTINGS"
echo "constant TARGET_TRIPLE := " >> "$STATIC_SETTINGS"
if [ `uname` = "Darwin" ]; then
    echo "'x86_64-apple-macosx10.8.0'" >> "$STATIC_SETTINGS"
else
    echo "'x86_64-pc-linux-gnu'" >> "$STATIC_SETTINGS"
fi
echo "constant GCC_EXE_ARGS:ImmutableArray<String> := [" >> "$STATIC_SETTINGS"
if [ `uname` != "Darwin" ]; then
    echo "'-lunwind'" >> "$STATIC_SETTINGS"
fi
echo "]" >> "$STATIC_SETTINGS"
echo "constant GCC_LIBRARY_ARGS:ImmutableArray<String> := [" >> "$STATIC_SETTINGS"
echo "]" >> "$STATIC_SETTINGS"
echo "constant LLC_EXE_ARGS := ['-O3'" >> "$STATIC_SETTINGS"
if [ `uname` = "Darwin" ]; then
    echo ", '-mattr=-avx'" >> "$STATIC_SETTINGS"
fi
echo "]" >> "$STATIC_SETTINGS"
echo "constant LLC_LIBRARY_ARGS:ImmutableArray<String> := ['-O3'" >> "$STATIC_SETTINGS"
if [ `uname` = "Darwin" ]; then
    echo ", '-mattr=-avx'" >> "$STATIC_SETTINGS"
else
    echo ", '-relocation-model=pic'" >> "$STATIC_SETTINGS"
fi
echo "]" >> "$STATIC_SETTINGS"
echo "constant PANDAGL_GCC_ARGS:ImmutableArray<String> := [" >> "$STATIC_SETTINGS"
if [ `uname` = "Darwin" ]; then
    echo "'-l', 'pandagl', '-framework', 'SDL2', '-framework', 'SDL2_image', " >> "$STATIC_SETTINGS"
    echo "'-L/opt/local/lib', '-lcairo', " >> "$STATIC_SETTINGS"
    echo "'-L', '/opt/local/lib', '-L', '\$PANDA_HOME/native/gl/lib/'" >> "$STATIC_SETTINGS"
else
    echo "'-lpandagl', '-lSDL2', '-lSDL2_image', '-L/usr/lib/SDL2', '-L/usr/lib/x86_64-linux-gnu/', " >> "$STATIC_SETTINGS"
    echo "'-L', '/opt/local/lib', '-L', '\$PANDA_HOME/native/gl/lib/'" >> "$STATIC_SETTINGS"
fi
echo "]" >> "$STATIC_SETTINGS"
echo "}" >> "$STATIC_SETTINGS"







echo "Compiling core (native)..."

mkdir -p $NATIVE_TARGET/core/c
$PANDAC -XnoCoreLib -f h -o $NATIVE_TARGET/core/c/panda.h $CORE_FILES
cd src/core/c
./build.sh
cd "$BASEDIR"

$PANDAC -XpreserveTempArtifacts -XnoCoreLib -f lib -o $NATIVE_TARGET/core/lib/PandaCoreClasses.o $CORE_FILES

mkdir -p $NATIVE_TARGET/core/lib

if [ $PLATFORM = "Darwin" ]; then
    libtool -undefined suppress -flat_namespace -dynamic $NATIVE_TARGET/core/c/libpanda.a \
        $NATIVE_TARGET/core/lib/PandaCoreClasses.o -o $NATIVE_TARGET/core/lib/libpanda.dylib
else
    gcc -shared -o $NATIVE_TARGET/core/lib/libpanda.so $NATIVE_TARGET/core/c/*.o \
        $NATIVE_TARGET/core/lib/PandaCoreClasses.o
fi

echo "Compiling pandac (native)..."

mkdir -p $NATIVE_TARGET/pandac/bin
$PANDAC -XpreserveTempArtifacts -o $NATIVE_TARGET/pandac/bin/pandac `find src/pandac/panda -name "*.panda"` \
    src/plex/panda/org/pandalanguage/plex/runtime/*.panda $NATIVE_TARGET/plex/src/Lexer.panda \
    $STATIC_SETTINGS

PANDAC=$NATIVE_TARGET/pandac/bin/pandac

echo building JavaScript libraries
mkdir -p build/js
JAVASCRIPT_TARGET="$TARGET/js"
mkdir -p $JAVASCRIPT_TARGET/core
cp src/core/js/*.js $JAVASCRIPT_TARGET/core
$PANDAC -f js -o $JAVASCRIPT_TARGET/core `find src/core/panda -name "*.panda"`

scripts/build_gl.sh
