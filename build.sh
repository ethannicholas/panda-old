#!/bin/bash

set -o nounset
set -o errexit
set -o pipefail

export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
$BASEDIR/scripts/build_all.sh

echo
echo Success!
echo pandac is at $BASEDIR/build/native/pandac/bin/pandac
echo be sure to set PANDA_HOME to $BASEDIR/build

if [ `uname` != "Darwin" ]; then
    echo for the time being, you need to add $BASEDIR/build/native/pandac/lib
    echo to your LD_LIBRARY_PATH
fi
