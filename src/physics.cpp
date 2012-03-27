#include "physics.hpp"
#include "sprite.hpp"
#include "SDL_Collide.h"

#ifdef WIN32
#include <SDL.h>
#else
#include <SDL/SDL.h>
#endif

#include <stdio.h>

Physics::Physics()
{
    fprintf(stderr, "Physics formalizing\n");
}

Physics::~Physics()
{
    fprintf(stderr, "Laws of physics deemed invalid");
}

bool Physics::init()
{
    gravity = 0.0f;
    return true;
}

bool Physics::checkCollision(Sprite* s1, Sprite* s2)
{
    SDL_Surface* a = s1->spriteSurface;
    SDL_Surface* b = s2->spriteSurface;
    float loc_ax = s1->x;
    float loc_ay = s1->y;
    float loc_bx = s2->x;
    float loc_by = s2->y;
    float result = SDL_BoundingCollide(a, loc_ax, loc_ay, b, loc_bx , loc_by);
    if (result)
    {
        fprintf(stderr, "There is a collission %d\n", result);
    }
    return false;
}
