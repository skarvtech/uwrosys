files=$(find . -type d -name 'build')
for f in $files
do
    rm -r $f
done

builddir=$(dirname "$0")'/build'
mkdir $builddir
cd $builddir
cmake ..
make
