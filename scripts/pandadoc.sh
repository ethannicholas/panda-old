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
    cat $BASEDIR/scripts/head.html $BASEDIR/scripts/toc.html > $BASEDIR/build/docs/$file.html
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
$PANDAC -f doc -o build/docs-tmp `find $CORE -name "*.panda"`

cd $BASEDIR/build/docs-tmp
for fullFile in `find . -name "*.xml"`
do
    file=${fullFile%.*}
    target=../docs/api/$file.html
    mkdir -p `dirname $target`
    xsltproc $BASEDIR/scripts/pandadoc.xsl $fullFile > $target
done

# FIXME
# Compiling to Java below as a workaround for a serious problem I haven't worked
# out yet. When compiled to native code, the program intermittently just stops 
# finding matches after a while.
#
# This is almost certainly my fault, but the cause is non-obvious. It seems to
# require an exec of the compiler, as when I replaced the pandac exec with a
# /bin/ls exec or a sleep, I was unable to reproduce the problem. But given that
# these things are running in separate processes, I'm not sure how they could be
# interfering with each other. And if it's not an interference issue, I'm not
# sure why replacing the exec with a different exec suddenly stops demonstrating
# the problem. FWIW, I haven't tried replacing the regex search with a non-regex
# search, but I expect that will also make the problem go away.
#
# Bah. Definitely requires further investigation, but for right now this 
# workaround seems to be avoiding the issue.
cd $BASEDIR
$PANDAC -f jar -o build/java/ProcessSources.jar scripts/ProcessSources.panda
java -jar build/java/ProcessSources.jar build/docs