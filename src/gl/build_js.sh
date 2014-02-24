#!/bin/bash

echo "Building GL (javascript)..."

export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/../.."
source $BASEDIR/scripts/setup-script.sh
cd $BASEDIR

mkdir -p $JS_TARGET/gl

mv $NATIVE_TARGET/gl/lib/pandagl.plink $NATIVE_TARGET/pandagl.plink.tmp # FIXME: leaving this around causes a build error due to the idiotic way I look fields and methods up on pass 2
$PANDAC -f js -o $JS_TARGET/gl src/gl/panda/panda/gl/*.panda src/gl/panda/panda/gl/events/*.panda src/gl/panda/panda/gl/images/*.panda src/gl/panda/panda/gl/shapes/*.panda
mv $NATIVE_TARGET/pandagl.plink.tmp $NATIVE_TARGET/gl/lib/pandagl.plink

cp -r src/gl/js/* $JS_TARGET/gl/