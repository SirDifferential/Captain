#include "particle.hpp"
#include <GL/glew.h>

Particle::Particle(ParticleSystem* m)
{
    motherObject = m;
}

Particle::~Particle()
{
}

void Particle::update(Vector3 vel)
{
    velocity = vel;
    location += velocity;
}

// Must be called from particle master object which
// opens with glBegin(GL_POINTS) and closes with glEnd()
void Particle::render()
{
    glPointSize(size);
    glColor4f(color.x, color.y, color.z, opacity);
    glVertex3f(location.x, location.y, location.z);
}
