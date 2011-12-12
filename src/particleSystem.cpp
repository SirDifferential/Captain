#include "particleSystem.hpp"
#include <GL/glew.h>

ParticleSystem::ParticleSystem(int n, float h, float w, Vector3 loc, float colorVariance, float color1, float color2, float color3)
{
    fprintf(stderr, "ParticleSystem constructing\n");
    numOfParticles = n;
    height = h;
    width = w;
    location = loc;
    for (unsigned int i = 0; i < numOfParticles; i++)
        particles.push_back(Particle(this));
    for (std::vector<Particle>::iterator iter = particles.begin(); iter != particles.end(); iter++)
    {
        Vector3 temp;
        // Random location within the bounds of the system
        temp.x = loc.x + width - (double(rand())/RAND_MAX)*width;
        temp.y = loc.y + height - (double(rand())/RAND_MAX)*height;
        temp.z = -1;
        iter->setLocation(temp);
        iter->setSize(1.0f);
        // High color variance == random component appears more
        // Color variance of 0 == completely defined color
        // Color variance of 1 == completely random color
        iter->setColorR(color1 - (double(rand())/RAND_MAX) * colorVariance);
        iter->setColorG(color2 - (double(rand())/RAND_MAX) * colorVariance);
        iter->setColorB(color3 - (double(rand())/RAND_MAX) * colorVariance);
    }
}

ParticleSystem::~ParticleSystem()
{
    fprintf(stderr, "ParticleSystem destructing\n");
}

void ParticleSystem::update(Vector3 vel)
{
    velocity = vel;
    location += velocity;
    for (std::vector<Particle>::iterator iter = particles.begin(); iter != particles.end(); iter++)
    {
        iter->update(velocity);
    }
}

void ParticleSystem::render()
{
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    for (std::vector<Particle>::iterator iter = particles.begin(); iter != particles.end(); iter++)
    {
        iter->render();
    }
    glEnd();
}
