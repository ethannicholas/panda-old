#!/bin/bash
export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/.."
export PANDA_HOME=$BASEDIR/build
export PATH=$PANDA_HOME/native/pandac/bin:$PATH
export PANDAC=$PANDA_HOME/native/pandac/bin/pandac
