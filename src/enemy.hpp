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

    float velocity_max;
    float directional_thruster_power;
    float thrust;
    float shipRotation;
    float brakePower;
public:
    Enemy(std::string name, std::string spritePath, Vector3 loc);
    ~Enemy();

    void operate();
    void think();
    void update();
    void render();

    void accelerate();
    void decelerate();
    void come_to_halt();
    void stop();
    void rotateLeft();
    void rotateRight();
    void strafeLeft();
    void strafeRight();
    void resetAllVectors();

    std::string getName() { return name; }
    boost::shared_ptr<Sprite> getSprite() { return enemySprite; }
};

#endif
