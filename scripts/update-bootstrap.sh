#/bin/bash
export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/.."
cd $BASEDIR
source scripts/setup-script.sh

STATIC_SETTINGS="$SHARED_TARGET/StaticSettings.panda"
$PANDAC -XnoCoreLib -XpreserveTempArtifacts -f c -o bootstrap/bootstrap.c `find src/pandac/panda -name "*.panda"` \
    `find src/core/panda -name "*.panda"` $STATIC_SETTINGS $SHARED_TARGET/PandaLRParser.panda
$PANDAC -XpreserveTempArtifacts -XnoCoreLib -f plink -o bootstrap/PandaCoreClasses.plink $CORE_FILES
$PANDAC -XnoCoreLib -f h -o bootstrap/include/panda.h $CORE_FILES
$NATIVE_TARGET/parsergenerator src/pandac/parser/grammar.grammar src/pandac/parser/grammar.errors bootstrap/GrammarParser.panda
$NATIVE_TARGET/parsergenerator src/pandac/parser/errors.grammar src/pandac/parser/errors.errors bootstrap/ErrorParser.panda
$NATIVE_TARGET/parsergenerator src/core/parser/json.grammar src/core/parser/json.errors bootstrap/JSONParser.panda
