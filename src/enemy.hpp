#ifndef _ENEMY_HPP_
#define _ENEMY_HPP_

#include <boost/shared_ptr.hpp>
#include "vector3.hpp"
class Sprite;

class Enemy
{
private:
    int id;
    std::string name;
    std::string spritePath;
    Vector3 location;
    Vector3 velocity;
    boost::shared_ptr<Sprite> enemySprite;
public:
    Enemy(std::string name, std::string spritePath, Vector3 loc);
    ~Enemy();

    void operate();
    void think();
    void update();
    void render();

    std::string getName() { return name; }
};

#endif
