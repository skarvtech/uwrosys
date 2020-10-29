files=$(find . -type d -name 'build')
for f in $files
do
    rm -r $f
done

