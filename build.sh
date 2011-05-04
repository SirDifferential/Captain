#/bin/sh

echo 'Removing old files'
rm ./run_captain
rm ./bin/data/Captain
cd ./src
echo 'Compiling...'
make
echo 'Moving executable to bin/data'
mv ./Captain ../bin/data
cd ..
echo 'Run from run_captain.sh'
