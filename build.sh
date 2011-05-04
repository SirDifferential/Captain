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
echo 'Linking'
ln -s ./bin/data/Captain run_captain
echo 'Now run the game from run_captain!'
