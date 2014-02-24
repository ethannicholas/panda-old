EXAMPLE_HOME="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
BASEDIR="$EXAMPLE_HOME/../.."
source $BASEDIR/scripts/setup-script.sh
cd $EXAMPLE_HOME

mkdir -p $NATIVE_TARGET/examples/bounce
$PANDAC -o $NATIVE_TARGET/examples/bounce/Bounce Bounce.panda
cp -r images $NATIVE_TARGET/examples/bounce

$NATIVE_TARGET/examples/bounce/Bounce