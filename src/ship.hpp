#ifndef __SHIP_HPP
#define __SHIP_HPP_

#include "square.hpp"
#include "vector3.hpp"
#include <vector>

class Ship
{
private:
    float mass;
	std::string name;
    
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;

	std::vector<Square> squares;

public:
	Ship();
    ~Ship();
};

#endif
