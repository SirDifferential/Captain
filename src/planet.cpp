#include "planet.hpp"
#include <iostream>

Planet::Planet()
{
}

// Construct a new stellar body with the mass, temperature, radius and location
// as the params. This is almost similar to the Sun.cpp, but for now we are
// keeping planets in their separate file as there is probably some different
// behaviour coming in the future
Planet::Planet(int m, int t, int r, int posX, int posY)
{
	mass = m;
	temperature = t;
	radius = r;
	position.x = posX;
	position.y = posY;
	
	std::cout << "=======" << std::endl;
	std::cout << "Created a new planet with following properties:" << std::endl;
	std::cout << "- mass: " << mass << std::endl;
	std::cout << "- temperature: " << temperature << std::endl;
	std::cout << "- radius: " << radius << std::endl;
	std::cout << "- position X: " << position.x << std::endl;
	std::cout << "- position Y: " << position.y << std::endl;
	std::cout << "=======" << std::endl;
}

Planet::~Planet()
{
}

void Planet::render()
{
}
