#!/bin/bash

echo "Building UI (java)..."

export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/../.."
source $BASEDIR/scripts/setup-script.sh
cd $BASEDIR

mkdir -p $JAVA_TARGET/ui/src
mkdir -p $JAVA_TARGET/ui/build
mkdir -p $JAVA_TARGET/ui/lib

mv $SHARED_TARGET/ui/lib/pandaui.plink $SHARED_TARGET/pandaui.plink.tmp # FIXME: leaving this around causes a build error due to the idiotic way I look fields and methods up on pass 2
$PANDAC -f java -o $JAVA_TARGET/ui/src src/ui/panda/panda/ui/*.panda src/ui/panda/panda/ui/events/*.panda src/ui/panda/panda/ui/images/*.panda src/ui/panda/panda/gl/*.panda
$PANDAC -f javah -o $JAVA_TARGET/ui/src src/ui/panda/panda/ui/*.panda src/ui/panda/panda/ui/events/*.panda src/ui/panda/panda/ui/images/*.panda src/ui/panda/panda/gl/*.panda
mv $SHARED_TARGET/pandaui.plink.tmp $SHARED_TARGET/ui/lib/pandaui.plink

cp -r src/ui/java/* $JAVA_TARGET/ui/src

cd $JAVA_TARGET/ui/src

javac -d ../build -cp .:$JAVA_TARGET/core/lib/PandaCoreClasses.jar panda/ui/*.java

cd ../build

jar cf pandaui.jar *

cp pandaui.jar ../lib
