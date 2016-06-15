#/bin/bash
export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/.."
cd $BASEDIR
source scripts/setup-script.sh

STATIC_SETTINGS="$SHARED_TARGET/StaticSettings.panda"
$PANDAC -XnoCoreLib -XpreserveTempArtifacts -f c -o $NATIVE_TARGET/pandac/bin/pandac.c `find src/pandac/panda -name "*.panda"` \
    `find src/core/panda -name "*.panda"` $STATIC_SETTINGS $SHARED_TARGET/PandaLRParser.panda
gcc -Wno-parentheses-equality -L/opt/local/lib -Lbuild/native/core/lib -lpanda -lgc -licui18n -licuuc -licudata -I build/native/core/c -I src/core/c -I /opt/local/include $NATIVE_TARGET/pandac/bin/pandac.c -o pandac