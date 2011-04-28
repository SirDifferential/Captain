#include "objectManager.hpp"
#include "programManager.hpp"

ObjectManager objectmgr;

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::render()
{
	for (int i = 0; i < shipVector.size(); i++)
	{
		Ship &s = shipVector[i];
		s.render();
	}
}
