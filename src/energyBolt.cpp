#include "energyBolt.hpp"
#include "manager.hpp"

EnergyBolt::EnergyBolt(Vector3 loc, Vector3 vel, float rotation)
{
    fprintf(stderr, "EnergyBolt constructing\n");
    location = loc;

    velocity.x = sin(rotation)*4.0f, + vel.x;
    velocity.y = cos(rotation)*4.0f, + vel.y;

    lifeTime = 3.0f;
    birthTime = manager.getTime();
    particles = boost::shared_ptr<ParticleSystem>(new ParticleSystem(100, 10, 10, location, 0.8, 0.2, 0.8, 0.4));
}

EnergyBolt::~EnergyBolt()
{
    fprintf(stderr, "EnergyBolt destructing\n");
}

void EnergyBolt::update()
{
    location = location + velocity;
    particles->update(velocity);
}

void EnergyBolt::render()
{
    update();
    particles->render();
}

// Returns false if this projectile must be killed
bool EnergyBolt::checkLife()
{
    if (birthTime+lifeTime > manager.getTime())
        return true;
    return false;
}
