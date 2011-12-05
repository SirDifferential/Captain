#include "ship.hpp"
#include "sprite.hpp"
#include "vector3.hpp"

Ship::Ship(std::string n, std::string spritePath)
{
    fprintf(stderr, "Creating new ship with name %s and sprite %s\n", name.c_str(), spritePath.c_str());
    name = n;
    boost::shared_ptr<Sprite> temp(new Sprite(spritePath));
    spritePtr = temp;
    location.x = 0;
    location.y = 0;
    location.z = 0;

    velocity.x = 0;
    velocity.y = 0;
    velocity.z = 0;

    thrust = 0.005;
}

Ship::~Ship()
{
}

void Ship::accelerate()
{
    fprintf(stderr, "Accelerating\n");
    if (spritePtr->rotation > 180)
    {
        velocity.x -= sin(spritePtr->rotation)*thrust;
        velocity.y -= cos(spritePtr->rotation)*thrust;
    } else
    {
        velocity.x += sin(spritePtr->rotation)*thrust;
        velocity.y += cos(spritePtr->rotation)*thrust;
    }
    fprintf(stderr, "Velocity x: %f, velocity: %f, velocity z: %d\n", velocity.x, velocity.y, velocity.z);
    //fprintf(stderr, "Location x: %f, location y: %f, location z: %d", location.x, location.y, location.z);
}

void Ship::decelerate()
{
    fprintf(stderr, "Decelerating\n");
    if (spritePtr->rotation > 180)
    {
        velocity.x -= sin(spritePtr->rotation)*thrust;
        velocity.y -= cos(spritePtr->rotation)*thrust;
    } else
    {
        velocity.x -= sin(spritePtr->rotation)*thrust;
        velocity.y -= cos(spritePtr->rotation)*thrust;
    }
}

void Ship::rotateLeft()
{
    fprintf(stderr, "Turning left\n");
    spritePtr->rotation += 5.0f;
    if (spritePtr->rotation > 360)
        spritePtr->rotation = 0.0f;
}

void Ship::rotateRight()
{
    fprintf(stderr, "Turning right\n");
    spritePtr->rotation -= 5.0f;
    if (spritePtr->rotation > 360)
        spritePtr->rotation = 0.0f;
}

void Ship::update()
{
    location = location + velocity;
    spritePtr->x = location.x;
    spritePtr->y = location.y;
}

void Ship::render()
{
    spritePtr->render();
}

void Ship::resetAllVectors()
{
    location.x = 0;
    location.y = 0;
    location.z = 0;

    velocity.x = 0;
    velocity.y = 0;
    velocity.z = 0;
}
