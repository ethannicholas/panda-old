EXAMPLE_HOME="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
BASEDIR="$EXAMPLE_HOME/../.."
source $BASEDIR/scripts/setup-script.sh
cd $EXAMPLE_HOME

mkdir -p $NATIVE_TARGET/examples/guess
$PANDAC -o $NATIVE_TARGET/examples/guess/Guess Guess.panda

$NATIVE_TARGET/examples/guess/Guess