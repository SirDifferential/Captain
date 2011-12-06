#ifndef _SHIP_HPP_
#define _SHIP_HPP_

#include <boost/shared_ptr.hpp>
#include "vector3.hpp"
#include "sprite.hpp"

class Ship
{
private:
    int id;
    std::string name;

    Vector3 location;
    Vector3 velocity;
    float shipRotation;     // Radians

    float thrust;

    boost::shared_ptr<Sprite> spritePtr;
public:
    Ship(std::string n, std::string spritePath);
    ~Ship();

    void update();
    void render();
    void accelerate();
    void decelerate();
    void rotateLeft();
    void rotateRight();
    void resetAllVectors();

    std::string getName() { return name; }
};

#endif
