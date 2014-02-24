export PANDA_HOME="$TARGET"

cd $BASEDIR

PANDAC=$NATIVE_TARGET/pandac/bin/pandac

echo building JavaScript libraries
mkdir -p build/js
JAVASCRIPT_TARGET="$TARGET/js"
mkdir -p $JAVASCRIPT_TARGET/core
cp src/core/js/*.js $JAVASCRIPT_TARGET/core
$PANDAC -f js -o $JAVASCRIPT_TARGET/core `find src/core/panda -name "*.panda"`

scripts/build_gl.sh

scripts/pandadoc.sh