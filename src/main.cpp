/*
Captain

Yet another game project
*/

#include "programManager.hpp"
#include <iostream>

// The main calls ProgramManager (singleton) which takes care
// of the looping, calling rendering, and pretty much everything
int main(int argc, char** argv)
{
	progmgr.work();
	progmgr.stop();

	std::cout << "Program exit point" << std::endl;
	return 0;
}
