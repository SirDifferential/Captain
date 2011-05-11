#ifndef __SUN_HPP_
#define __SUN_HPP_

#include "vector3.hpp"

class Sun
{
private:
	int mass;
	int temperature;
	Vector3 position;
public:
	Sun();
	Sun(int mass, int temperature, int posX, int posY);
	~Sun();
};

#endif
