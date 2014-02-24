#!/bin/bash

set -o nounset
set -o errexit
set -o pipefail

export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
$BASEDIR/scripts/build_all.sh

echo pandac is at $BASEDIR/build/native/pandac/bin/pandac
echo be sure to set PANDA_HOME to $BASEDIR/build