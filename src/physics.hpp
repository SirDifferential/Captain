#ifndef __PHYSICS_HPP_
#define __PHYSICS_HPP_

class Sprite;

class Physics
{
private:
    int id;
    float gravity;
public:
    Physics();
    ~Physics();

    bool init();
    bool checkCollision(Sprite* s1, Sprite* s2);
};

#endif
