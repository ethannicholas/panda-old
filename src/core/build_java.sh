#/bin/bash

echo "Building core (java)..."

export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/../.."
source $BASEDIR/setup-script.sh
cd $BASEDIR

mkdir -p $JAVA_TARGET/core/java
mkdir -p $JAVA_TARGET/core/lib
mkdir -p $JAVA_TARGET/core/classes

$PANDAC -f java -o $JAVA_TARGET/core/java `find src/core/panda -name "*.panda"`

$PANDAC -f javah -o $JAVA_TARGET/core/java `find src/core/panda -name "*.panda"`

cp -r src/core/java/* $JAVA_TARGET/core/java

cd $JAVA_TARGET/core/java
javac -d ../classes `find . -name "*.java"`
cd ../classes
jar cvf ../lib/panda.jar *

