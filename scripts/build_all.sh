#!/bin/bash
export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/.."
cd "$BASEDIR"
source scripts/setup-script.sh

export PANDA_HOME=$BASEDIR/build

echo "Building bootstrap compiler..."
mkdir -p $SHARED_TARGET/core/lib
cp bootstrap/PandaCoreClasses.plink $SHARED_TARGET/core/lib
src/core/c/build.sh
gcc -g -Wno-parentheses-equality -L/opt/local/lib -Lbuild/native/core/c -Lbuild/native/core/lib -lpanda -lgc -licui18n -licuuc -licudata -lc++abi -I bootstrap/include -I src/core/c -I /opt/local/include bootstrap/bootstrap.c -o build/bootstrap

export PANDAC="$BASEDIR/build/bootstrap"
mkdir -p build/native/core/c

echo "Compiling core libraries..."

mkdir -p $NATIVE_TARGET/core/c
$PANDAC -XnoCoreLib -f h -o $NATIVE_TARGET/core/c/panda.h $CORE_FILES

$PANDAC -XpreserveTempArtifacts -XnoCoreLib -f plink -o $SHARED_TARGET/core/lib/PandaCoreClasses.plink $CORE_FILES
$PANDAC -XpreserveTempArtifacts -XnoCoreLib -f lib -o $NATIVE_TARGET/core/lib/PandaCoreClasses.o $CORE_FILES

mkdir -p $NATIVE_TARGET/core/lib

if [ $PLATFORM = "Darwin" ]; then
    libtool -undefined suppress -flat_namespace -dynamic $NATIVE_TARGET/core/c/libpanda.a \
        $NATIVE_TARGET/core/lib/PandaCoreClasses.o -o $NATIVE_TARGET/core/lib/libpanda.dylib
else
    gcc -shared -o $NATIVE_TARGET/core/lib/libpanda.so $NATIVE_TARGET/core/c/*.o \
        $NATIVE_TARGET/core/lib/PandaCoreClasses.o
fi

echo "Creating parser..."
mkdir -p $NATIVE_TARGET
mkdir -p $SHARED_TARGET
$PANDAC -O -o $NATIVE_TARGET/parsergenerator src/pandac/parser/ParserGenerator.panda bootstrap/GrammarParser.panda bootstrap/ErrorParser.panda

echo "Compiling pandac..."

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
echo "constant PANDAUI_GCC_ARGS:ImmutableArray<String> := [" >> "$STATIC_SETTINGS"
if [ `uname` = "Darwin" ]; then
    echo "'-l', 'pandaui', '-l', 'SDL2', '-l', 'SDL2_image', " >> "$STATIC_SETTINGS"
    echo "'-L/opt/local/lib', " >> "$STATIC_SETTINGS"
    echo "'-L', '/opt/local/lib', '-L', '\$PANDA_HOME/native/ui/lib/'" >> "$STATIC_SETTINGS"
else
    echo "'-lpandaui', '-lSDL2', '-lSDL2_image', '-L/usr/lib/SDL2', '-L/usr/lib/x86_64-linux-gnu/', " >> "$STATIC_SETTINGS"
    echo "'-L', '/opt/local/lib', '-L', '\$PANDA_HOME/native/ui/lib/'" >> "$STATIC_SETTINGS"
fi
echo "]" >> "$STATIC_SETTINGS"
echo "}" >> "$STATIC_SETTINGS"

mkdir -p $NATIVE_TARGET/pandac/bin
$PANDAC -XpreserveTempArtifacts -o $NATIVE_TARGET/pandac/bin/pandac `find src/pandac/panda -name "*.panda"` \
    $STATIC_SETTINGS $SHARED_TARGET/PandaLRParser.panda
