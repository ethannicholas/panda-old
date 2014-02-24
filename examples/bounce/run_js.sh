echo "JavaScript support is not enabled yet, sorry :-("
exit

EXAMPLE_HOME="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
BASEDIR="$EXAMPLE_HOME/../.."
source $BASEDIR/scripts/setup-script.sh
cd $EXAMPLE_HOME

echo $JS_TARGET/examples/bounce
mkdir -p $JS_TARGET/examples/bounce
$PANDAC -f js -o $JS_TARGET/examples/bounce/ Bounce.panda
cp -r images $JS_TARGET/examples/bounce/

open $JS_TARGET/examples/bounce/main.html