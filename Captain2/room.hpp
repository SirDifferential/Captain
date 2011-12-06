#ifndef _ROOM_HPP_
#define _ROOM_HPP_

#include <boost/shared_ptr.hpp>
#include "menu.hpp"
#include "sprite.hpp"
#include "ship.hpp"
#include <map>

typedef std::map<std::string, boost::shared_ptr<Sprite> > spriteContainer;
typedef std::map<std::string, boost::shared_ptr<Ship> > shipContainer;

class Room
{
private:
    std::string name;
    int roomNumber;
    int roomType;
    boost::shared_ptr<Menu> menuPtr;
    boost::shared_ptr<Ship> playerShip;

    spriteContainer spriteMap;
    spriteContainer::iterator spriteIterator;
    shipContainer shipMap;
    shipContainer::iterator shipIterator;
    double roomStartTime;
    bool firstRun;
    double timePerPicture; // For cinematics
    double pictureChangeTime; // For cinematics
    std::string music;
public:
    Room(std::string s, std::string mus, int n, int t);
    Room(std::string s, std::string mus, int n, boost::shared_ptr<Menu> m);
    ~Room();
    void operate();
    boost::shared_ptr<Sprite> getSprite(std::string name);
    void addSprite(std::string name, boost::shared_ptr<Sprite> s);
    void removeSprite(std::string name);
    void addShip(boost::shared_ptr<Ship> s);
    void removeShip(std::string name);
    boost::shared_ptr<Menu> giveMenu() { return menuPtr; }
    void iterateSprites();

    boost::shared_ptr<Ship> getPlayerShip();
    std::string getName() { return name; }
    int getType() { return roomType; }
};

#endif
