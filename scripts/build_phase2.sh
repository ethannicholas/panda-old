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
        src/core/panda/panda/io/*.panda src/core/panda/panda/math/*.panda\
        src/core/panda/panda/parser/*.panda build/shared/JSONParser.panda"
STATIC_SETTINGS="$SHARED_TARGET/StaticSettings.panda"

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
    $STATIC_SETTINGS $SHARED_TARGET/PandaLRParser.panda

PANDAC=$NATIVE_TARGET/pandac/bin/pandac

#echo building JavaScript libraries
#mkdir -p build/js
#JAVASCRIPT_TARGET="$TARGET/js"
#mkdir -p $JAVASCRIPT_TARGET/core
#cp src/core/js/*.js $JAVASCRIPT_TARGET/core
#$PANDAC -XnoCoreLib -O -f js -o $JAVASCRIPT_TARGET/core `find src/core/panda -name "*.panda"`

scripts/build_ui.sh
