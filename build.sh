#/bin/sh

echo "#################################################"
echo "#                                               #"
echo "# You have invoked the build script for Captain #"
echo "#  Before mailing me about bad code, make sure  #"
echo "#     you have all the required libraries       #"
echo "#                                               #"
echo "#           This project depends on:            #"
echo "#              - SDL                            #"
echo "#              - SDL_mixer                      #"
echo "#              - SDL_image                      #"
echo "#              - SDL_ttf                        #"
echo "#              - OpenGL                         #"
echo "#              - glew                           #"
echo "#              - boost                          #"
echo "#                                               #"
echo "#   My name is Jesse Kaukonen and my email is   #"
echo "#   my.name at the mail offered by Google       #"
echo "#                                               #"
echo "#################################################"

echo "Press return to continue"

read dummy_input

echo 'Removing old files'
cd ./src
rm ./Kapteeni
make clean

echo 'Compiling...'
make

if [ ! -f ./Kapteeni ]
then
	echo "There was an error in compiling. See the compiler logs above"
	echo "In case it isn't a simple library problem, mail the developer"
	exit 1
else
	echo "Build successful"
	echo "All done!"
	echo "Make sure to be in the ./src directory when running the binary"
fi

