#ifndef _ENERGYBOLT_HPP_
#define _ENERGYBOLT_HPP_

#include "vector3.hpp"
#include "particleSystem.hpp"
#include <boost/shared_ptr.hpp>

class EnergyBolt
{
private:
    int id;
    float width;
    Vector3 location;
    Vector3 velocity;
    int numOfParticles;
    float lifeTime;
    float birthTime;
    boost::shared_ptr<ParticleSystem> particles;
public:
    EnergyBolt(Vector3 loc, Vector3 vel, float rotation);
    ~EnergyBolt();

    void update();
    void render();
    bool checkLife();
};

#endif
