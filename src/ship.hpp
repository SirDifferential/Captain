#ifndef _SHIP_HPP_
#define _SHIP_HPP_

#include "vector3.hpp"
#include "sprite.hpp"
#include <vector>
#include <set>
#include <boost/shared_ptr.hpp>

class EnergyBolt;

class Ship
{
private:
    int id;
    std::string name;

    Vector3 location;
    Vector3 velocity;
    Vector3 velocity_max;
    float directional_thruster_power;   // Strafing
    float shipRotation;     // Radians

    float thrust;
    bool useAutomaticZooming;   // If camera zooms based on velocity
    boost::shared_ptr<Sprite> spritePtr;
    float scale;
    float cameraHeight; // How high from the ship the camera is

    float weapon1FireTime;
    float weapon1Cooldown;
    float brakePower;

    std::set<boost::shared_ptr<EnergyBolt> > weapon1Shots;
public:
    Ship(std::string n, std::string spritePath);
    ~Ship();

    void update();
    void render();
    void accelerate();
    void decelerate();
    void stop();
    void rotateLeft();
    void rotateRight();
    void strafeLeft();
    void strafeRight();
    void resetAllVectors();
    void cameraZoomIn();
    void cameraZoomOut();
    void fireWeapon1();
    void come_to_halt();

    void setScale(float f);
    void setLocation(Vector3 in) { location = in; }
    Vector3 getLocation() { return location; }
    Vector3 getVelocity() { return velocity; }
    std::string getName() { return name; }
    void setUseAutoZoom(bool in) { useAutomaticZooming = in; }
    bool getUseAutoZoom() { return useAutomaticZooming; }
    float getRotation() { return shipRotation; }
};

#endif
