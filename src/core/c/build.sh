#/bin/bash

export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/../../.."
source $BASEDIR/scripts/setup-script.sh

cd $C_SRC
C_TARGET="$NATIVE_TARGET/core/c"
mkdir -p "$C_TARGET"
mkdir -p "$NATIVE_TARGET/core/lib"
COMPILE="gcc -Werror $INCLUDES -fPIC -ferror-limit=0 -c"
STRICT="-Wall -Wextra" # -fcatch-undefined-behavior isn't supported on older Macs
COMPILE_CPP="g++ -Werror $INCLUDES -fPIC -ferror-limit=0 -c"
$COMPILE $STRICT -o $C_TARGET/pandalib.o pandalib.c
$COMPILE_CPP -o $C_TARGET/pandaExceptions.o pandaExceptions.cpp

$COMPILE_CPP -o $C_TARGET/realString.o realString.cc
cd $BASEDIR/src/external/dtoa
$COMPILE_CPP -o $C_TARGET/bignum-dtoa.o bignum-dtoa.cc
$COMPILE_CPP -o $C_TARGET/bignum.o bignum.cc
$COMPILE_CPP -o $C_TARGET/cached-powers.o cached-powers.cc
$COMPILE_CPP -o $C_TARGET/diy-fp.o diy-fp.cc
$COMPILE_CPP -o $C_TARGET/double-conversion.o double-conversion.cc
$COMPILE_CPP -o $C_TARGET/fast-dtoa.o fast-dtoa.cc
$COMPILE_CPP -o $C_TARGET/fixed-dtoa.o fixed-dtoa.cc
$COMPILE_CPP -o $C_TARGET/strtod.o strtod.cc
cd $C_TARGET
ar cr libpanda.a *.o