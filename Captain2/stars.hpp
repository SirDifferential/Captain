#ifndef _STARS_HPP_
#define _STARS_HPP_

#include "vector3.hpp"
#include <vector>

class Stars
{
private:
    class Star
    {
    private:
        Stars* motherStars;
    public:
        Vector3 location;
        Vector3 velocity;
        Vector3 color;
        float size;
        
        void render();
        void update();
        Star(Stars* starSystem);
    };

    int id;
    std::string name;
    std::vector<Star> stars;
    int numberOfStars;
    float opacity;

    Vector3 location;
    Vector3 topLeft;
    Vector3 topRight;
    Vector3 bottomLeft;
    Vector3 bottomRight;
public:
    Stars(std::string s, int quantity, float colorVariance, Vector3 coords);
    ~Stars();
    
    void update();
    void render();
    bool checkRenderBoundary();
};

#endif
