#ifndef _SPRITE_HPP_
#define _SPRITE_HPP_

#include <string>
#ifdef WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>
#else
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#endif

#include <GL/glew.h>

class Sprite
{
public:

    SDL_Surface* spriteSurface;	// SDL_Surface containing the colour data
    int w, h;					// Resolution of the sprite
    int x, y, z;				// Location in the world
    float scale;                // Scaling factor
    GLuint id;					// The OpenGL handle
    GLenum format;				// The colour format (RGB, RGBA, LUMINANCE)
    float opacity;				// The transparency of the sprite
    std::string name;			// The name of our sprite
    Sprite();
    Sprite(int sizeX, int sizeY);
    Sprite(std::string &path);
    virtual ~Sprite();
    SDL_Color col;
    bool useAlpha;
    float rotation;

    void setPixel(SDL_Surface* pSurface , int x , int y , SDL_Color color);
    SDL_Color getPixel(SDL_Surface* pSurface , int x , int y);
    void setAllPixels(SDL_Surface* pSurface, SDL_Color color);
    void convertToGreyScale();
    GLenum check(SDL_Surface *surface, std::string &path);
    GLenum checkGeneric(SDL_Surface *surface);

    void bind(int unit);
    void unbindAll();

    virtual void render();
    
    std::string getName() { return name; }
    void setWidth(int n) { w = n; }
    void setHeight(int n) { h = n; }
    int getWidth() { return w; }
    int getHeight() { return h; }
    void setName(std::string s) { name = s; }
    void setSpriteSurface(SDL_Surface* surf) { spriteSurface = surf; }
    SDL_Surface* getSpriteSurface() { return spriteSurface; }
};

#endif
