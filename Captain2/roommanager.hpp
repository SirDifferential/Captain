#ifndef __ROOMMANAGER_HPP_
#define __ROOMMANAGER_HPP_

#include "room.hpp"
#include <map>
#include <vector>

//typedef std::map<std::string, boost::shared_ptr<Room> > roomContainer;

class RoomManager
{
private:
    int id;
    //std::map<std::string, boost::shared_ptr<Room> > roomMap;
    //std::map<std::string, boost::shared_ptr<Room> >::iterator roomIterator;
    std::vector<boost::shared_ptr<Room> > roomVector;
    std::vector<boost::shared_ptr<Room> >::iterator roomIter;
    int activeRoom;
public:
    RoomManager();
    ~RoomManager();
    bool init();
    boost::shared_ptr<Room> getRoom(std::string n);
    void addRoom(boost::shared_ptr<Room> r);

    void work();
};

#endif
