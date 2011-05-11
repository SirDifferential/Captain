#include "toolbox.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Toolbox toolbox;

Toolbox::Toolbox()
{
	timesRandomized = 0;
	srand(time(0));
}

Toolbox::~Toolbox()
{
}

int Toolbox::giveRandomInt()
{
	timesRandomized++;
	return rand();
}

int Toolbox::giveRandomInt(int min, int max)
{
	return ((rand()%(max-min))+min);
}
