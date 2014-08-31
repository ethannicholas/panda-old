export BASEDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )/.."
cd $BASEDIR
source scripts/setup-script.sh

echo Building docs...

mkdir -p build/docs
cd $BASEDIR/docs
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
cp scripts/panda.css docs/*.panda build/docs
cp scripts/pandadoc.css docs/*.panda build/docs/api
cp scripts/pandacode.css docs/*.panda build/docs/api
$PANDAC -f doc -o build/docs-tmp `find $CORE -name "*.panda"`

cd $BASEDIR/build/docs-tmp
for fullFile in `find . -name "*.xml"`
do
    file=${fullFile%.*}
    target=../docs/api/$file.html
    mkdir -p `dirname $target`
    xsltproc $BASEDIR/scripts/pandadoc.xsl $fullFile > $target
done
