#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include "vector3.hpp"
#include <GL/glew.h>
#include "sprite.hpp"
#include <boost/shared_ptr.hpp>

class Renderer
{
private:
    int id;
    Vector3 eye;
    Vector3 center;
    bool firstRun;
    std::vector<boost::shared_ptr<Sprite> > sprites;
    
public:
    Renderer();
    ~Renderer();
    
    void moveCamera();
    void clearScreen();
    void renderBackground();
    void renderMain();
    void renderForeground();
    void render();
    void renderObject(	GLenum primitiveType, int indiceCount, GLenum datatype,
                std::vector<int> indices, std::vector<double> vertices,
                std::vector<double> normals, Vector3 location,
                float rotation, float scale);
    void calculateLights();
    
};

extern Renderer renderer;

#endif
