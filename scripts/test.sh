export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/.."
cd $BASEDIR

rm -f build/TestHarness
$PANDAC -o build/TestHarness src/test/TestHarness.panda
build/TestHarness "$PANDAC" src build