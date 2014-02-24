#/bin/bash
export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/.."
cd $BASEDIR

mkdir -p bootstrap/shared/core/lib
cp build/shared/core/lib/PandaCoreClasses.plink bootstrap/shared/core/lib

mkdir -p bootstrap/java/pandac
mkdir -p bootstrap/java/core/lib
cp build/java/pandac/bin/pandac.jar bootstrap/java/pandac/bin
cp build/java/core/lib/PandaCoreClasses.jar bootstrap/java/pandac/bin