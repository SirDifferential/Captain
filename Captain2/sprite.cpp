/*
This class contains a sprite. It is created either by
1. Defining a resolution
2. Defining a path to an image file
The sprite can be used by either SDL or OpenGL. The constructor first builds an SDL_Surface,
then constructs a new glTexture2D with the pixel data from the SDL_Surface.
The default rendering function puts the texture on a flat 2D plane and maps the texture on it.
The model is then rendered at coordinates (x,y,z)

There are some operations that are performed on the sprite pixel data. After each of these
operations the glTexture2D is reseted and re-created, so the operations are somewhat heavy.
convertToGrayscale() is one of them.
*/

#include "sprite.hpp"
#include "toolbox.hpp"
#include "opengl.hpp"
#include <assert.h>

Sprite::Sprite()
{
}

// Constructs a sprite with some size. Useful for shaders
Sprite::Sprite(int sizeX, int sizeY)
{
    w = sizeX;
    h = sizeY;
    x = 0;
    y = 0;
    scale = 1.0;
    id = 0;
    glGenTextures(1, &id);
    assert(id);
    opacity = 1.0f;
    name = tbox.resolutionToString(w, h);
    
    glBindTexture(GL_TEXTURE_2D, id);
    
    GLuint target = GL_TEXTURE_2D;
    spriteSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
    
    // Get the texture format. We will want to create it according to the SDL surface
    format = checkGeneric(spriteSurface);
    
    // Lock the surface for direct pixel acccess
    SDL_LockSurface(spriteSurface);
    
    SDL_Color color;
    
    // Init the surface with random colors. Useful for debugging
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            color = tbox.getRandomColor();
            setPixel(spriteSurface, i, j, color);
        }
    }
    
    // Done, unlock
    SDL_UnlockSurface(spriteSurface);
    
    // Create the actual OpenGL texture
    glTexImage2D(target,
        0,
        format,
        spriteSurface->w,
        spriteSurface->h,
        0,
        format,
        GL_UNSIGNED_BYTE,
        spriteSurface->pixels);

    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    fprintf(stderr, "New sprite built with following properties: Generic sprite %s\n", name.c_str());
}

// Constructs a sprite based on a loaded image file. Good for textures
Sprite::Sprite(std::string &path) :
    x(0), y(0)
{
    x = 1;
    y = 1;
    w = 1024;
    h = 1024;
    scale = 0.1;
    id = 0;
    glGenTextures(1, &id);
    assert(id);
    opacity = 0.0f;
    glBindTexture(GL_TEXTURE_2D, id);
    name = path;

    col.r = 1.0f;
    col.g = 1.0f;
    col.b = 1.0f;

    GLuint target = GL_TEXTURE_2D;
    bool buildMipmaps = true;
    spriteSurface = NULL;
    fprintf(stderr, "Loading: %s\n", path.c_str());
    if (target == GL_TEXTURE_2D)
    {
        spriteSurface = IMG_Load(path.c_str());
        std::string error = IMG_GetError();
        fprintf(stderr, "IMG_Load returns: %s\n", error.c_str());
        format = check(spriteSurface, path);
        w = spriteSurface->w;
        h = spriteSurface->h;
        
        glTexImage2D(target,
            0,
            format,
            spriteSurface->w,
            spriteSurface->h,
            0,
            format,
            GL_UNSIGNED_BYTE,
            spriteSurface->pixels);
        
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    fprintf(stderr, "New sprite built with following properties: data sprite %s, %d%s%d\n", name.c_str(), w, "x", h);
}

Sprite::~Sprite()
{
    assert(spriteSurface);
    fprintf(stderr, "Sprite destructing: %s\n", name.c_str());
    SDL_FreeSurface(spriteSurface);
}

// When constructing, make sure the input file is good
GLenum Sprite::check(SDL_Surface *surface, std::string &path)
{
    if (!surface) {
        fprintf(stderr, "Surface is empty: %s\n", path.c_str());
        throw std::string("SDL surface error:") += path;
    }
    
    /*if ((surface->w & (surface->w - 1)) != 0 ||
        (surface->h & (surface->h - 1)) != 0) {
        SDL_FreeSurface(surface);
        fprintf(stderr, "Image size not in power of two\n");
        throw "Image size must be in power of two";
    }
    */
    // Select textures format
    GLenum format;
    if (surface->format->BytesPerPixel == 4)
        format = GL_RGBA;
    else if (surface->format->BytesPerPixel == 3)
        format = GL_RGB;
    else if (surface->format->BytesPerPixel == 1)
        format = GL_LUMINANCE;
    else {
        SDL_FreeSurface(surface);
        throw "Image format must be 8, 24 or 32 bits per pixel.";
    }
    return format;
}

GLenum Sprite::checkGeneric(SDL_Surface* pSurface)
{
    // Select texture format
    GLenum format;
    if (pSurface->format->BytesPerPixel == 4) {
        format = GL_RGBA;
    }
    else if (pSurface->format->BytesPerPixel == 3)
    {
        format = GL_RGB;
    }
    else if (pSurface->format->BytesPerPixel == 1) {
        format = GL_LUMINANCE;
    }
    else {
        SDL_FreeSurface(pSurface);
        throw "Image format must be 8, 24 or 32 bits per pixel.";
    }
    return format;
}

// Sets one pixel of a SDL_Surface to desired colour
void Sprite::setPixel(SDL_Surface *pSurface, int x, int y, SDL_Color color)
{
    Uint32 col = SDL_MapRGB(pSurface->format, color.r, color.g, color.b);
    char* pPosition = (char*) pSurface->pixels;
    pPosition += (pSurface->pitch * y);
    pPosition += (pSurface->format->BytesPerPixel * x);
    memcpy(pPosition, &col, pSurface->format->BytesPerPixel);
}

// Set all pixels of a surface to one color
void Sprite::setAllPixels(SDL_Surface* pSurface, SDL_Color col)
{
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            setPixel(pSurface, i, j, col);
        }
    }
}

// Returns a SDL_Color of a specific pixel in a SDL_Surface
SDL_Color Sprite::getPixel(SDL_Surface *pSurface, int x, int y)
{
    SDL_Color color;
    Uint32 col = 0;
    char* pPosition = (char*) pSurface->pixels;
    pPosition += (pSurface->pitch * y);
    pPosition += (pSurface->format->BytesPerPixel * x);
    memcpy(&col, pPosition, pSurface->format->BytesPerPixel);
    SDL_GetRGB(col, pSurface->format, &color.r, &color.g, &color.b);
    return color;
}

void Sprite::convertToGreyScale()
{
    GLuint target = GL_TEXTURE_2D;
    SDL_LockSurface(spriteSurface);
    SDL_Color colorBW;
    
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            colorBW = tbox.getBWColor(getPixel(spriteSurface, i, j));
            setPixel(spriteSurface, i, j, colorBW);
        }
    }
    
    SDL_UnlockSurface(spriteSurface);
    
    glTexImage2D(target,
        0,
        format,
        spriteSurface->w,
        spriteSurface->h,
        0,
        format,
        GL_UNSIGNED_BYTE,
        spriteSurface->pixels);
    
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Sprite::bind(int unit)
{
    assert(unit >= 0 && unit < 8);
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Sprite::unbindAll()
{
    for (int i=0; i<8; i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void Sprite::render()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    
    glTranslatef(x, y, 0);
    glScalef(scale, scale, scale);
    
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, id);
    glColor4f(col.r, col.g, col.b, opacity);
    
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2f(-w, -h);
        glTexCoord2f(1, 1); glVertex2f(w, -h);
        glTexCoord2f(1, 0); glVertex2f(w, h);
        glTexCoord2f(0, 0); glVertex2f(-w, h);
    glEnd();
    
    glPopMatrix();
}
