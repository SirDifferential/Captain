#ifndef _ROOMMANAGER_HPP_
#define _ROOMMANAGER_HPP_

#include "room.hpp"
#include <map>
#include <vector>

class RoomManager
{
private:
    int id;
    std::vector<boost::shared_ptr<Room> > roomVector;
    std::vector<boost::shared_ptr<Room> >::iterator roomIter;
    int activeRoom;
public:
    RoomManager();
    ~RoomManager();
    bool init();
    boost::shared_ptr<Room> getRoom(std::string n);
    int getRoomIndex(std::string);
    void addRoom(boost::shared_ptr<Room> r);
    void nextRoom();
    void changeRoom(std::string name);
    boost::shared_ptr<Room> giveCurrentRoom();
    void work();
};

#endif
