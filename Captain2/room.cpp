#include "room.hpp"
#include "manager.hpp"

Room::Room(std::string s, std::string mus, int n, int t)
{
    fprintf(stderr, "Room creating with name %s and number %d and type %d\n", s.c_str(), n, t);
    name = s;
    roomNumber = n;
    roomType = t;
    music = mus;
    firstRun = true;
}

Room::~Room()
{
}

Room::Room(std::string s, std::string mus, int n, boost::shared_ptr<Menu> m)
{
    name = s;
    roomNumber = n;
	roomType = 2;
	menuPtr = m;
    music = mus;
}

void Room::operate()
{
	if (roomType == 1)	// An arena
	{
        if (firstRun)
        {
            // If room has a new music, change it
            if (music.compare("no music") != 0)
            {
                if (manager.getAudioMgr()->getCurrentMusic().compare(music) != 0)
                    manager.getAudioMgr()->changeMainMusic(music);
            }
            firstRun = false;
        }
        for (spriteIterator = spriteMap.begin(); spriteIterator != spriteMap.end(); spriteIterator++)
            (*spriteIterator).second->render();
        for (shipIterator = shipMap.begin(); shipIterator != shipMap.end(); shipIterator++)
        {
            (*shipIterator).second->update();
            (*shipIterator).second->render();
        }
	} else if (roomType == 2) // A menu
	{
        // Allow browsing in the menu
        if (spriteMap.size() > 0)
        {
            for (spriteIterator = spriteMap.begin(); spriteIterator != spriteMap.end(); spriteIterator++)
                (*spriteIterator).second->render();
        }
		menuPtr->update();
		menuPtr->render();
	} else if (roomType == 3) // Cinematics
    {
        if (firstRun)
        {
            roomStartTime = manager.getTime();
            timePerPicture = 4;
            pictureChangeTime = roomStartTime;
            spriteIterator = spriteMap.begin();
            firstRun = false;
        }

        if (manager.getTime() - pictureChangeTime > timePerPicture)
        {
            pictureChangeTime = manager.getTime();
            spriteIterator++;
        }
        if (spriteIterator == spriteMap.end())
            manager.getRoomMgr()->nextRoom();
        else
            (*spriteIterator).second->render();
	} else if (roomType == 4) // Static text rooms
    {
        if (firstRun)
        {
            spriteIterator = spriteMap.begin();
            firstRun = false;
        }

        if (spriteIterator == spriteMap.end())
            manager.getRoomMgr()->nextRoom();
        else
            (*spriteIterator).second->render();
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

void Room::addShip(boost::shared_ptr<Ship> s)
{
    shipMap[s->getName()] = s;
    if (s->getName().compare("Player ship") == 0)
        playerShip = s;
}

void Room::removeShip(std::string name)
{
    shipIterator = shipMap.find(name.c_str());
    if (shipIterator != shipMap.end())
    {
        shipMap.erase(shipIterator);
    } else
    {
        fprintf(stderr, "No ship found to delete! Ship: %s, Room: %d\n", name.c_str(), roomNumber);
    }
}

void Room::iterateSprites()
{
    spriteIterator++;
}

boost::shared_ptr<Ship> Room::getPlayerShip()
{
    if (playerShip == NULL)
        fprintf(stderr, "Ship is null\n");
    return playerShip;
}
