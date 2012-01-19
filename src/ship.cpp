#include "ship.hpp"
#include "sprite.hpp"
#include "vector3.hpp"
#include "renderer.hpp"
#include "manager.hpp"
#include "energyBolt.hpp"

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

    velocity_max = 2.5f;
    directional_thruster_power = 0.01f;
    thrust = 0.005f;
    shipRotation = 0.0f;
    useAutomaticZooming = true;
    cameraHeight = 200.0f;

    weapon1Cooldown = 1.0f;
    weapon1FireTime = 0.0f;
}

Ship::~Ship()
{
}

void Ship::accelerate()
{
    velocity.x += -1*sin(shipRotation)*thrust;
    velocity.y += cos(shipRotation)*thrust;
}

void Ship::decelerate()
{
    velocity.x -= -1*sin(shipRotation)*thrust;
    velocity.y -= cos(shipRotation)*thrust;
}

void Ship::stop()
{
    velocity.x = 0;
    velocity.y = 0;
    velocity.z = 0;
}

void Ship::rotateLeft()
{
    shipRotation += 0.01f;
    if (shipRotation > 6.28318)  // Radians, 2*pi
        shipRotation = 0.0f;
    spritePtr->rotation = shipRotation*(180/3.14159);    // Sprite rotation in degrees
}

void Ship::rotateRight()
{
    shipRotation -= 0.01;
    if (shipRotation > 6.28318)
        shipRotation = 0.0f;
    spritePtr->rotation = shipRotation*(180/3.14159);
}

// Strafing is done by calculating a vector perpendicular to
// the velocity vector and multiplying by the thruster power.
// The maths is:
//
//              |
//    .(v^ |-)  |         . (v^)
//      .       |       .
//        .     |     .
//          .   |   .
//            . | .
//  ____________|_____________
//              | .
//              |   .
//              |     .  
//              |        . (- v^ |-)
// |- means perpendicular
//  v^ |- = (-v^.y, v^.x)
void Ship::strafeLeft()
{
    Vector3 normal_vector;
    normal_vector.x = -1*directional_thruster_power * cos(shipRotation);
    normal_vector.y = -1*directional_thruster_power * sin(shipRotation);
    velocity += normal_vector;
}

void Ship::strafeRight()
{
    Vector3 normal_vector;
    normal_vector.x = directional_thruster_power * cos(shipRotation);
    normal_vector.y = directional_thruster_power * sin(shipRotation);
    velocity += normal_vector;
}

void Ship::update()
{
    // Cap velocity
    if (velocity.x > velocity_max.x)
        velocity.x = velocity_max.x;
    if (velocity.x < -1 && (abs(velocity.x) > velocity_max.x))
        velocity.x = velocity_max.x * -1;

    if (velocity.y > velocity_max.y)
        velocity.y = velocity_max.y;
    if (velocity.y < -1 && (abs(velocity.y) > velocity_max.y))
        velocity.y = velocity_max.y * -1;

    location = location + velocity;
    spritePtr->x = location.x;
    spritePtr->y = location.y;

    // Check if any projectiles should be deleted
    std::set<boost::shared_ptr<EnergyBolt> >::iterator iter = weapon1Shots.begin();
    while (iter != weapon1Shots.end())
    {
        if ((*iter)->checkLife() == false)
        {
            iter = weapon1Shots.erase(iter);
        } else {
            ++iter;
        }
    }
}

void Ship::render()
{
    if (useAutomaticZooming)
    {
        cameraHeight = (abs(velocity.length()*0.5) * 1000);
        if (cameraHeight < 200)
            cameraHeight = 200;
        if (cameraHeight > 1000)
            cameraHeight = 1000;
        renderer.moveCamera(location.x, location.y, cameraHeight);
    } else
    {
        if (cameraHeight < 200)
            cameraHeight = 200;
        if (cameraHeight > 1000)
            cameraHeight = 1000;
        renderer.moveCamera(location.x, location.y, cameraHeight);
    }
    spritePtr->render();
    for (std::set<boost::shared_ptr<EnergyBolt> >::iterator iter = weapon1Shots.begin(); iter != weapon1Shots.end(); iter++)
    {
        (*iter)->render();
    }
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

void Ship::cameraZoomIn()
{
    cameraHeight += 3.0f;
}

void Ship::cameraZoomOut()
{
    cameraHeight -= 3.0f;
}

void Ship::fireWeapon1()
{
    if (weapon1FireTime > manager.getTime() - weapon1Cooldown)
    {
        fprintf(stderr, "Cooling down\n");
    } else
    {
        fprintf(stderr, "Firing\n");
        weapon1FireTime = manager.getTime();
        boost::shared_ptr<EnergyBolt> firedShot(new EnergyBolt(location, velocity, shipRotation));
        weapon1Shots.insert(firedShot);
    }
}

void Ship::setScale(float f)
{
    scale = f;
    spritePtr->scale = f;
}
