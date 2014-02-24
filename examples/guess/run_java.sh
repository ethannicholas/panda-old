EXAMPLE_HOME="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
BASEDIR="$EXAMPLE_HOME/../.."
source $BASEDIR/scripts/setup-script.sh
cd $EXAMPLE_HOME

mkdir -p $JAVA_TARGET/examples/guess
$PANDAC -f jar -o $JAVA_TARGET/examples/guess/Guess.jar Guess.panda

java -jar $JAVA_TARGET/examples/guess/Guess.jar