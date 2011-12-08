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
    float nativeHeight; // How far the camera is normally
    
public:
    Renderer();
    ~Renderer();
    
    void moveCamera(float coord_x, float coord_y, float coord_z);
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
    Vector3 getCameraLocation() { return eye; }
    float getNativeHeight() { return nativeHeight; }
};

extern Renderer renderer;

#endif
