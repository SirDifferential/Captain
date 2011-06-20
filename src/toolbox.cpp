#include "toolbox.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <string>

Toolbox tbox;

// Constructs our toolbox. Sets the random seed
Toolbox::Toolbox()
{
	timesRandomized = 0;
	srand(time(0));
}

Toolbox::~Toolbox()
{
}

// Returns a random integer
int Toolbox::giveRandomInt()
{
	timesRandomized++;
	return rand();
}

// Returns a random integer in range (min, max)
int Toolbox::giveRandomInt(int min, int max)
{
	return ((rand()%(max-min))+min);
}

// Converts a char into a string
std::string Toolbox::charToString(char c)
{
	std::stringstream stream;
	std::string out;
	stream << c;
	stream >> out;
	
	return out;
}

// Converts std::vector<double> into std::vector<int>
// Used by the objLoader
std::vector<int> Toolbox::doubleVectorToIntVector(std::vector<double> in)
{
	std::vector<int> output;
	for (int i = 0; i < in.size(); i++)
	{
		output.push_back(int(in.at(i)));
	}
	return output;
}
