#!/bin/bash

echo "Building GL (java)..."

export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/../.."
source $BASEDIR/scripts/setup-script.sh
cd $BASEDIR

mkdir -p $JAVA_TARGET/gl/src
mkdir -p $JAVA_TARGET/gl/build
mkdir -p $JAVA_TARGET/gl/lib

mv $SHARED_TARGET/gl/lib/pandagl.plink $SHARED_TARGET/pandagl.plink.tmp # FIXME: leaving this around causes a build error due to the idiotic way I look fields and methods up on pass 2
$PANDAC -f java -o $JAVA_TARGET/gl/src src/gl/panda/panda/gl/*.panda src/gl/panda/panda/gl/events/*.panda src/gl/panda/panda/gl/images/*.panda src/gl/panda/panda/gl/shapes/*.panda
$PANDAC -f javah -o $JAVA_TARGET/gl/src src/gl/panda/panda/gl/*.panda src/gl/panda/panda/gl/events/*.panda src/gl/panda/panda/gl/images/*.panda src/gl/panda/panda/gl/shapes/*.panda
mv $SHARED_TARGET/pandagl.plink.tmp $SHARED_TARGET/gl/lib/pandagl.plink

cp -r src/gl/java/* $JAVA_TARGET/gl/src

cd $JAVA_TARGET/gl/src

javac -d ../build -cp .:$JAVA_TARGET/core/lib/PandaCoreClasses.jar panda/gl/*.java

cd ../build

jar cf pandagl.jar *

cp pandagl.jar ../lib
