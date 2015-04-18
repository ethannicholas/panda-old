export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/.."
cd $BASEDIR

rm -f build/TestHarness.jar
$PANDAC_JAVA -f jar -o build/TestHarness.jar src/test/TestHarness.panda
java -jar build/TestHarness.jar --java $JAVA_HOME/bin/java "$PANDAC_JAVA" src build