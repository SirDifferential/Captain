/*
Captain

Yet another game project
*/

#include <iostream>
#include "programManager.hpp"

int main(int argc, char** argv)
{
	progmgr.work();
	progmgr.stop();

	std::cout << "Program exit point" << std::endl;
	return 0;
}