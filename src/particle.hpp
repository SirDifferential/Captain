#ifndef _PARTICLE_HPP_
#define _PARTICLE_HPP_

#include "Vector3.hpp"

class ParticleSystem;

class Particle
{
private:
    int id;
    float size;
    Vector3 location;
    Vector3 velocity;
    Vector3 color;
    float opacity;
    ParticleSystem* motherObject;
public:
    Particle(ParticleSystem* m);
    ~Particle();

    void update(Vector3 loc);
    void render();

    void setColorR(float i) { color.x = i; }
    void setColorG(float i) { color.y = i; }
    void setColorB(float i) { color.z = i; }
    void setLocation(Vector3 loc) { location = loc; }
    void setSize(float s) { size = s; }
};

#endif
