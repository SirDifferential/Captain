#ifndef __OBJECTMANAGER_HPP_
#define __OBJECTMANAGER_HPP_

#include <vector>
#include "ship.hpp"
#include "square.hpp"

class ObjectManager
{
private:
	std::vector<Ship> shipVector;
public:
	ObjectManager();
	~ObjectManager();
};

#endif
