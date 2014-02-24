#!/bin/bash
export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/.."
export PANDA_HOME=$BASEDIR/build
export PATH=$PATH:$PANDA_HOME/native/pandac/bin
export PANDAC=$PANDA_HOME/native/pandac/bin/pandac
