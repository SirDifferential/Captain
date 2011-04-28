#ifndef __OBJECTMANAGER_HPP_
#define __OBJECTMANAGER_HPP_

#include <vector>
#include "ship.hpp"
#include "sprite.hpp"
#include "arena.hpp"

class ObjectManager
{
private:
	std::vector<Ship> shipVector;
public:
	ObjectManager();
	~ObjectManager();

	void render();
};

extern ObjectManager objectmgr;

#endif
