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
    bool useAutomaticZooming;   // If camera zooms based on velocity
    boost::shared_ptr<Sprite> spritePtr;
    float cameraHeight; // How high from the ship the camera is
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
    void resetAllVectors();
    void cameraZoomIn();
    void cameraZoomOut();

    void setLocation(Vector3 in) { location = in; }
    Vector3 getLocation() { return location; }
    std::string getName() { return name; }
    void setUseAutoZoom(bool in) { useAutomaticZooming = in; }
    bool getUseAutoZoom() { return useAutomaticZooming; }
};

#endif
