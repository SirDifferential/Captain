#ifndef _PARTICLESYSTEM_HPP_
#define _PARTICLESYSTEM_HPP_

#include "particle.hpp"
#include "Vector3.hpp"
#include <vector>

class ParticleSystem
{
private:
    int id;
    Vector3 location;
    Vector3 velocity;
    int numOfParticles;
    float width;
    float height;
    std::vector<Particle> particles;
public:
    ParticleSystem(int n, float h, float w, Vector3 loc, float colorVariance, float color1, float color2, float color3);
    ~ParticleSystem();

    void update(Vector3 loc);
    void render();
};

#endif
