#!/bin/bash

echo "Building pandac (java)..."

export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/../.."
source $BASEDIR/setup-script.sh
cd $BASEDIR

mkdir -p $JAVA_TARGET/pandac/src
mkdir -p $JAVA_TARGET/pandac/build

$PANDAC -f java -o $JAVA_TARGET/pandac/src `find src/pandac/panda -name "*.panda"`

cd $JAVA_TARGET/pandac/src

javac -d ../build -cp .:$JAVA_TARGET/core/lib/panda.jar org/pandalanguage/pandac/compiler/*.java

cd ../build

jar cf $JAVA_TARGET/pandac/pandac.jar *
