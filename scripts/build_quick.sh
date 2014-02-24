#!/bin/bash

export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/.."
cd $BASEDIR
source scripts/setup-script.sh
export PANDA_HOME=bootstrap
PANDAC="java -ea -Xmx1g -jar bootstrap/java/pandac/bin/pandac.jar -L $NATIVE_TARGET/core/lib $@"
PANDAC_SRC=src/pandac/panda/org/pandalanguage/pandac
export PANDA_HOME=build
export DYLD_LIBRARY_PATH="$NATIVE_TARGET/core/lib"
STATIC_SETTINGS=$SHARED_TARGET/StaticSettings.panda

echo "Compiling pandac (native)..."

mkdir -p $NATIVE_TARGET/pandac/bin
$PANDAC -o $NATIVE_TARGET/pandac/bin/pandac `find src/pandac/panda -name "*.panda"` \
    src/plex/panda/org/pandalanguage/plex/runtime/*.panda $NATIVE_TARGET/plex/src/Lexer.panda \
    $STATIC_SETTINGS
