#!/bin/bash

export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/.."
cd $BASEDIR

echo "Building PLex (Java)..."

mkdir -p $JAVA_TARGET/plex/bin
$PANDAC -f jar -o $JAVA_TARGET/plex/bin/plex.jar \
        src/pandac/panda/org/pandalanguage/pandac/tree/Position.panda\
        src/plex/panda/org/pandalanguage/plex/*.panda\
        src/plex/panda/org/pandalanguage/plex/runtime/*.panda
