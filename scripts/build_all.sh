#!/bin/bash
export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/.."
cd "$BASEDIR"

source scripts/build_phase1.sh
source scripts/build_phase2.sh
