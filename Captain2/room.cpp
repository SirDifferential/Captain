#include "room.hpp"

Room::Room(std::string s, int n)
{
    fprintf(stderr, "Room creating with name %s and number %d\n", s.c_str(), n);
    name = s;
    roomNumber = n;
    roomType = 1;
}

Room::~Room()
{
}

Room::Room(std::string s, int n, boost::shared_ptr<Menu> m)
{
    name = s;
    roomNumber = n;
	roomType = 2;
	menuPtr = m;
}

void Room::operate()
{
	if (roomType == 1)	// An arena
	{
        for (spriteIterator = spriteMap.begin(); spriteIterator != spriteMap.end(); spriteIterator++)
            (*spriteIterator).second->render();
	} else if (roomType == 2) // A menu
	{
        if (spriteMap.size() > 0)
        {
            for (spriteIterator = spriteMap.begin(); spriteIterator != spriteMap.end(); spriteIterator++)
                (*spriteIterator).second->render();
        }
		menuPtr->update();
		menuPtr->render();
	}
}

boost::shared_ptr<Sprite> Room::getSprite(std::string name)
{
    spriteIterator = spriteMap.find(name.c_str());
    if (spriteIterator != spriteMap.end())
    {
        return spriteMap[name.c_str()];
    } else
    {
        fprintf(stderr, "Requested sprite not found! Sprite: %s, room: %d", name.c_str(), roomNumber);
        boost::shared_ptr<Sprite> nullPointer;
        return nullPointer;
    }
}

void Room::addSprite(std::string name, boost::shared_ptr<Sprite> s)
{
    spriteMap[name] = s;
}

void Room::removeSprite(std::string name)
{
    spriteIterator = spriteMap.find(name.c_str());
    if (spriteIterator != spriteMap.end())
    {
        spriteMap.erase(spriteIterator);
    } else
    {
        fprintf(stderr, "No sprite found to delete! Sprite: %s, Room: %d", name.c_str(), roomNumber);
    }
}
