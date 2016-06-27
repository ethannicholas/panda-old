#!/bin/bash
export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/.."
cd $BASEDIR

source scripts/setup-script.sh
src/ui/build_native.sh
#src/ui/build_js.sh