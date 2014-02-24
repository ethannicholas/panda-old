EXAMPLE_HOME="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
BASEDIR="$EXAMPLE_HOME/../.."
source $BASEDIR/scripts/setup-script.sh
cd $EXAMPLE_HOME

mkdir -p $NATIVE_TARGET/examples/wumpus
$PANDAC -o $NATIVE_TARGET/examples/wumpus/Wumpus Wumpus.panda

$NATIVE_TARGET/examples/wumpus/Wumpus