#ifndef __PLANET_HPP_
#define __PLANET_HPP_

#include "vector3.hpp"

class Planet
{
private:
	int mass;
	int temperature;
	int radius;
	Vector3 position;
public:
	Planet();
	Planet(int mass, int temperature, int radius, int posX, int posY);
	~Planet();
	
	void render();
};

#endif
