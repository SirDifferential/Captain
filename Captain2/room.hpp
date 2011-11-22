#ifndef __ROOM_HPP_
#define __ROOM_HPP_

#include <boost/shared_ptr.hpp>
#include "menu.hpp"
#include "sprite.hpp"
#include <map>

typedef std::map<std::string, boost::shared_ptr<Sprite> > spriteContainer;

class Room
{
private:
    std::string name;
    int roomNumber;
    int roomType;
    boost::shared_ptr<Menu> menuPtr;

    spriteContainer spriteMap;
    spriteContainer::iterator spriteIterator;
public:
    Room(std::string s, int n);
    Room(std::string s, int n, boost::shared_ptr<Menu> m);
    ~Room();
    void operate();
    boost::shared_ptr<Sprite> getSprite(std::string name);
    void addSprite(std::string name, boost::shared_ptr<Sprite> s);
    void removeSprite(std::string name);
    boost::shared_ptr<Menu> giveMenu() { return menuPtr; }

    std::string getName() { return name; }
};

#endif
