#ifndef __SHIP_HPP
#define __SHIP_HPP_

#include "vector3.hpp"

class Ship
{
private:
    
	Ship();
    ~Ship();

    float mass;
	std::string name;
    
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;
public:
};

#endif
