#include "ship.hpp"
#include "sprite.hpp"
#include "vector3.hpp"
#include "renderer.hpp"

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

    thrust = 0.002;
    shipRotation = 0.0f;
}

Ship::~Ship()
{
}

void Ship::accelerate()
{
    fprintf(stderr, "Accelerating\n");
    velocity.x += -1*sin(shipRotation)*thrust;
    velocity.y += cos(shipRotation)*thrust;
}

void Ship::decelerate()
{
    fprintf(stderr, "Decelerating\n");
    velocity.x -= -1*sin(shipRotation)*thrust;
    velocity.y -= cos(shipRotation)*thrust;
}

void Ship::rotateLeft()
{
    fprintf(stderr, "Turning left\n");
    shipRotation += 0.01f;
    if (shipRotation > 6.28318)  // Radians
        shipRotation = 0.0f;
    spritePtr->rotation = shipRotation*(180/3.14159);    // Sprite rotation in degrees
}

void Ship::rotateRight()
{
    fprintf(stderr, "Turning right\n");
    shipRotation -= 0.01;
    if (shipRotation > 6.28318)
        shipRotation = 0.0f;
    spritePtr->rotation = shipRotation*(180/3.14159);
}

void Ship::update()
{
    location = location + velocity;
    spritePtr->x = location.x;
    spritePtr->y = location.y;
}

void Ship::render()
{
    float cameraHeight = (abs(velocity.x) + abs(velocity.y) * 1000);
    if (cameraHeight < 200)
        cameraHeight = 200;
    if (cameraHeight > 1000)
        cameraHeight = 1000;
    renderer.moveCamera(location.x, location.y, cameraHeight);
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
