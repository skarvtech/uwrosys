files=$(find . -type d -name 'build')
for f in $files
do
    rm -r $f
done

#old_dir=$PWD
#build_dir=$(dirname "$0")/build
#mkdir $build_dir
#cd $build_dir
#cmake ..
#make
#cd $PWD
