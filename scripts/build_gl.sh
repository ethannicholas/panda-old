#!/bin/bash
export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/.."
cd $BASEDIR

source scripts/setup-script.sh
src/gl/build_native.sh
src/gl/build_java.sh
src/gl/build_js.sh