#!/bin/bash

echo "Building ui (javascript)..."

export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/../.."
source $BASEDIR/scripts/setup-script.sh
cd $BASEDIR

mkdir -p $JS_TARGET/ui

mv $NATIVE_TARGET/ui/lib/pandaui.plink $NATIVE_TARGET/pandaui.plink.tmp # FIXME: leaving this around causes a build error due to the idiotic way I look fields and methods up on pass 2
$PANDAC -f js -o $JS_TARGET/ui src/ui/panda/panda/ui/*.panda src/ui/panda/panda/ui/events/*.panda src/ui/panda/panda/ui/images/*.panda src/ui/panda/panda/gl/*.panda
mv $NATIVE_TARGET/pandaui.plink.tmp $NATIVE_TARGET/ui/lib/pandaui.plink

cp -r src/ui/js/* $JS_TARGET/ui/