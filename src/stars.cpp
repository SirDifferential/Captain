#include "stars.hpp"
#include "renderer.hpp"
#include <GL/glew.h>

Stars::Stars(std::string s, int quantity, float colorVariance, Vector3 coords)
{
    name = s;
    numberOfStars = quantity;
    for (unsigned int i = 0; i < numberOfStars; i++)
        stars.push_back(Star(this));
    for (std::vector<Star>::iterator iter = stars.begin(); iter != stars.end(); iter++)
    {
        iter->location.x = (double(rand())/RAND_MAX)*1000;
        iter->location.y = (double(rand())/RAND_MAX)*1000;
        iter->location.z = -1*(double(rand())/RAND_MAX)*10;

        iter->color.x = 1.0-(double(rand())/RAND_MAX) * colorVariance;
        iter->color.y = 1.0-(double(rand())/RAND_MAX) * colorVariance;
        iter->color.z = 1.0-(double(rand())/RAND_MAX) * colorVariance;

        iter->size = (rand()/RAND_MAX);
        iter->velocity.x = 0;
        iter->velocity.y = 0;
        iter->velocity.z = 0;
    }

    location.x = coords.x;
    location.y = coords.y;
    location.z = coords.z;

    // Used for checking render boundary, that is if the stars will be rendered
    topLeft.x = location.x - 500;
    topLeft.y = location.y + 500;
    topRight.x = location.x + 500;
    topRight.y = location.y + 500;
    bottomLeft.x = location.x - 500;
    bottomLeft.y = location.y - 500;
    bottomRight.x = location.x + 500;
    bottomRight.y = location.y - 500;
}

Stars::~Stars()
{
}

// Sees if these stars are in render range
// Not required right now as this is handled by Starmap
bool Stars::checkRenderBoundary()
{
    Vector3 cameraLocation = renderer.getCameraLocation();
    if (cameraLocation.x > topLeft.x-1500 &&
        cameraLocation.x < topRight.x+1500 &&
        cameraLocation.y < topLeft.y+1500 &&
        cameraLocation.y > bottomLeft.y-1500)
    {
        // These stars are in area that requires rendering
        return true;
    }
    return false;
}

void Stars::render()
{
    //if (checkRenderBoundary() == true)
    //{
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING);
        glDisable(GL_BLEND);
        glEnable(GL_POINT_SMOOTH);

        glBegin(GL_POINTS);
        for (unsigned int i = 0; i < stars.size(); i++)
        {
            glPointSize(stars[i].size);
            stars[i].render();
        }
        glEnd();
    //}
}

// Asks each star in the star system if it wants to update
void Stars::update()
{
    //for (unsigned int i = 0; i < stars.size(); i++)
    //    stars[i].update();
}

// Constructor for single Star object
// In a Stars object
// With a pointer parameter to a Stars object
// Assigns the mother cluster of stars to which this star belongs
Stars::Star::Star(Stars* mother)
{
    this->motherStars = mother;
}

// Render function for a single star in the star group
void Stars::Star::render()
{
    glColor4f(color.x, color.y, color.z, motherStars->opacity);
    glVertex3f(location.x + motherStars->location.x, location.y + motherStars->location.y, -1);
}

// Does this single star in the star system want to update?
void Stars::Star::update()
{
}

