#include "opengl.hpp"
#include "manager.hpp"

#define NOMUSIC

#ifdef WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <windows.h>
#else
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#endif

#include <GL/glew.h>
#include <GL/glut.h>

Opengl opengl;

Opengl::Opengl()
{
    fprintf(stderr, "Making friends with OpenGL...\n");
    // Default failsafe settings
    screenX = 640;
    screenY = 480;
    screenBPP = 32;
    fps = 60;
    limit_fps = true;
    fullscreen = false;
}

Opengl::~Opengl()
{
    fprintf(stderr, "Bidding farewells with the graphics libraries...\n");
    TTF_Quit();
    SDL_Quit();
}

bool Opengl::start()
{
    fprintf(stderr, "Initializing: SDL\n");
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_WM_SetCaption("Generic Demo Template", NULL);
    fprintf(stderr, "Initializing: SDL_ttf\n");
    TTF_Init();
    fprintf(stderr, "Initializing: Video mode\n");
    if (fullscreen)
        SDL_SetVideoMode(screenX, screenY, screenBPP, SDL_OPENGL |SDL_FULLSCREEN);
    else
        SDL_SetVideoMode(screenX, screenY, screenBPP, SDL_OPENGL |SDL_RESIZABLE);
    fprintf(stderr, "Initializing: OpenGL Glew\n");
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error starting Glew: %s \n", glewGetErrorString(err));
        manager.getEnter();
        manager.stop();
        return false;
    }
    fprintf(stderr, "Using Glew version %s \n", glewGetString(GLEW_VERSION));
    fprintf(stderr, "OpenGL init finished\n");
    return true;
}

float Opengl::giveTicks()
{
    return SDL_GetTicks();
}

void Opengl::swapBuffers()
{
    SDL_GL_SwapBuffers();
}

void Opengl::setFullscreen(bool fs) { fullscreen = fs; }
void Opengl::setScreenX(int x) { screenX = x; }
void Opengl::setScreenY(int y) { screenY = y; }
void Opengl::setBPP(int b) { screenBPP = b; }
void Opengl::setFPS(int f) { fps = f; }
void Opengl::setLimitFPS(bool b) { limit_fps = b; }
