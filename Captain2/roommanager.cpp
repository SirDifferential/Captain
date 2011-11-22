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
    std::string path1 = "data/2D/logo_1024x1024.png";
    boost::shared_ptr<Sprite> spritePtr(new Sprite(path1));
    boost::shared_ptr<Room> introRoom(new Room("Intro", 1));
    introRoom->addSprite("intro picture", spritePtr);

    boost::shared_ptr<Menu> menuPtr(new Menu);
    boost::shared_ptr<Room> menuRoom(new Room("Main menu", 2, menuPtr));
    path1 = "data/2D/menubg_1024x1024.png";
    boost::shared_ptr<Sprite> spritePtr2(new Sprite(path1));
    menuRoom->addSprite("menubg", spritePtr2);
    roomVector.push_back(menuRoom);
   
    boost::shared_ptr<Room> room1Ptr(new Room("First level", 3));

    room1Ptr->addSprite("Logo", spritePtr);
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

boost::shared_ptr<Room> RoomManager::giveCurrentRoom()
{
    return roomVector.at(activeRoom);
}
