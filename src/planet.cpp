#include "planet.hpp"
#include <iostream>

Planet::Planet()
{
}

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
