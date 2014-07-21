#!/bin/bash
set -o nounset
set -o errexit
set -o pipefail

export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/.."
export PLATFORM=`uname`

source $BASEDIR/scripts/setup.sh

export LD_LIBRARY_PATH=$BASEDIR/build/native/core/lib
export DYLD_LIBRARY_PATH=$BASEDIR/build/native/core/lib
export TARGET=$BASEDIR/build
export NATIVE_TARGET=$TARGET/native
export JAVA_TARGET=$TARGET/java
export SHARED_TARGET=$TARGET/shared
export JS_TARGET=$TARGET/js
export C_SRC="$BASEDIR/src/core/c"
export C_TARGET="$NATIVE_TARGET/core/c"
export EXTERNAL_SRC="$BASEDIR/src/external"
export INCLUDES="-I$C_SRC -I$C_TARGET -I$EXTERNAL_SRC -I/opt/local/include -I/usr/include/cairo"
