export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/.."
cd $BASEDIR
source scripts/setup-script.sh

echo Building docs...

mkdir -p build/md-copy
cp docs/*.md build/md-copy
$PANDAC -f jar -o build/java/ExtractSources.jar scripts/ExtractSources.panda
java -jar build/java/ExtractSources.jar build/md-copy

mkdir -p build/docs
cd $BASEDIR/build/md-copy
for fullFile in *.md
do
    file=${fullFile%.*}
    cp $BASEDIR/scripts/head.html $BASEDIR/build/docs/$file.html
    $BASEDIR/bootstrap/shared/Markdown.pl $fullFile >> $BASEDIR/build/docs/$file.html
    cat $BASEDIR/scripts/tail.html >> $BASEDIR/build/docs/$file.html
done

# Note: this is completely temporary. Eventually the XSL stylesheet processing
# and such will be incorporated directly into pandac; but for now it needs a bit
# of help generating the final docs.

cd $BASEDIR
CORE=src/core/panda
mkdir -p build/docs-tmp
mkdir -p build/docs/api
cp docs/styles/*.css docs/*.panda build/docs
cp docs/styles/*.css build/docs/api
mkdir -p build/docs/images
mkdir -p build/docs/api/images
mkdir -p build/docs/scripts
mkdir -p build/docs/api/scripts
cp docs/images/* build/docs/images
cp docs/images/* build/docs/api/images
cp docs/scripts/* build/docs/scripts
cp docs/scripts/* build/docs/api/scripts

$PANDAC -f doc -o build/docs-tmp `find $CORE -name "*.panda"`
mkdir -p build/docs/api/source
cp -r build/docs-tmp/source/* build/docs/api/source

cd $BASEDIR/build/docs-tmp
for fullFile in `find . -name "*.xml"`
do
    file=${fullFile%.*}
    target=../docs/api/$file.html
    mkdir -p `dirname $target`
    xsltproc $BASEDIR/scripts/pandadoc.xsl $fullFile > $target
done

cd $BASEDIR
pandac scripts/AddToC.panda -o build/native/AddToC
build/native/AddToC scripts/toc.html build/docs/api/index.html build/docs

$PANDAC -o build/native/ProcessSources scripts/ProcessSources.panda
build/native/ProcessSources build/docs