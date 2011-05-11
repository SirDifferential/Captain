#include "toolbox.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Toolbox toolbox;

Toolbox::Toolbox()
{
}

Toolbox::~Toolbox()
{
}

int Toolbox::giveRandomInt()
{
	return rand();
}

int Toolbox::giveRandomInt(int max)
{
	return int((double(rand())/RAND_MAX)*max);
}
