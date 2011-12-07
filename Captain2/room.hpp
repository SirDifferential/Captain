#ifndef _ROOM_HPP_
#define _ROOM_HPP_

#include <boost/shared_ptr.hpp>
#include "menu.hpp"
#include "options.hpp"
#include "sprite.hpp"
#include "ship.hpp"
#include "stars.hpp"
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
    boost::shared_ptr<Options> optionsPtr;

    spriteContainer spriteMap;
    spriteContainer::iterator spriteIterator;
    shipContainer shipMap;
    shipContainer::iterator shipIterator;
    double roomStartTime;
    bool firstRun;
    double timePerPicture; // For cinematics
    double pictureChangeTime; // For cinematics
    std::string music;
    std::vector<boost::shared_ptr<Stars> > starsVector;
public:
    Room(std::string s, std::string mus, int n, int t);
    Room(std::string s, std::string mus, int n, boost::shared_ptr<Menu> m);
    Room(std::string s, std::string mus, int n, boost::shared_ptr<Options> o);
    ~Room();
    void operate();
    boost::shared_ptr<Sprite> getSprite(std::string name);
    void addSprite(std::string name, boost::shared_ptr<Sprite> s);
    void removeSprite(std::string name);
    void addShip(boost::shared_ptr<Ship> s);
    void removeShip(std::string name);
    void addStars(boost::shared_ptr<Stars> s);
    boost::shared_ptr<Menu> giveMenu() { return menuPtr; }
    boost::shared_ptr<Options> giveOptions() { return optionsPtr; }
    void iterateSprites();

    boost::shared_ptr<Ship> getPlayerShip();
    std::string getName() { return name; }
    int getType() { return roomType; }
};

#endif
