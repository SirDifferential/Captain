#include "roommanager.hpp"

typedef std::pair<std::string, boost::shared_ptr<Room> > roomPair;

RoomManager::RoomManager()
{
    fprintf(stderr, "RoomManager constructing...\n");
}

RoomManager::~RoomManager()
{
    fprintf(stderr, "RoomManager destructing...\n");
}

bool RoomManager::init()
{   
    fprintf(stderr, "RoomManager creating rooms\n");
    boost::shared_ptr<Room> introRoom(new Room("Intro", 1, 3));
    std::string path1 = "data/2D/logo_1024x1024.png";
    boost::shared_ptr<Sprite> introSpritePtr1(new Sprite(path1));
    introRoom->addSprite("intro picture", introSpritePtr1);
    path1 = "data/2D/stars2_1024x1024.png";
    boost::shared_ptr<Sprite> introSpritePtr2(new Sprite(path1));
    introRoom->addSprite("intro picture 2", introSpritePtr2);
    path1 = "data/2D/stars3_1024x1024.png";
    boost::shared_ptr<Sprite> introSpritePtr3(new Sprite(path1));
    introRoom->addSprite("intro picture 3", introSpritePtr3);
    path1 = "data/2D/stars4_1024x1024.png";
    boost::shared_ptr<Sprite> introSpritePtr4(new Sprite(path1));
    introRoom->addSprite("intro picture 4", introSpritePtr4);
    
    roomVector.push_back(introRoom);

    boost::shared_ptr<Menu> menuPtr(new Menu);
    boost::shared_ptr<Room> menuRoom(new Room("Main menu", 2, menuPtr));
    path1 = "data/2D/menubg_1024x1024.png";
    boost::shared_ptr<Sprite> spritePtr2(new Sprite(path1));
    menuRoom->addSprite("menubg", spritePtr2);
    roomVector.push_back(menuRoom);
   
    boost::shared_ptr<Room> room1Ptr(new Room("First level", 100, 1));

    boost::shared_ptr<Room> helpRoom(new Room("Help", 900, 4));
    path1 = "data/2D/help.png";
    boost::shared_ptr<Sprite> helpSpritePtr(new Sprite(path1));
    helpRoom->addSprite("help", helpSpritePtr);
    roomVector.push_back(helpRoom);

    roomVector.push_back(room1Ptr);
    activeRoom = 0;
    return true;
}

boost::shared_ptr<Room> RoomManager::getRoom(std::string name)
{
    for (roomIter = roomVector.begin(); roomIter != roomVector.end(); roomIter++)
    {
        if ((*roomIter)->getName().compare(name))
            return (*roomIter);
    }

    fprintf(stderr, "Requested room not found: %s", name.c_str());
    boost::shared_ptr<Room> nullPointer;
    return nullPointer;
}

int RoomManager::getRoomIndex(std::string name)
{
    int i = 0;
    for (roomIter = roomVector.begin(); roomIter != roomVector.end(); roomIter++)
    {
        if ((*roomIter)->getName().compare(name) == 0)
            return i;
        i++;
    }

    fprintf(stderr, "Requested room not found: %s", name.c_str());
    return -1;
}

void RoomManager::addRoom(boost::shared_ptr<Room> r)
{
}

void RoomManager::work()
{
    roomVector.at(activeRoom)->operate();
}

void RoomManager::nextRoom()
{
    if (roomVector.size() > activeRoom)
        activeRoom++;
}

void RoomManager::changeRoom(std::string name)
{
    int index = getRoomIndex(name);
    if (index != -1)
        activeRoom = index;
}

boost::shared_ptr<Room> RoomManager::giveCurrentRoom()
{
    return roomVector.at(activeRoom);
}
