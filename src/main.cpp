/*
Captain

Yet another game project
*/

#ifdef WIN32
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <windows.h>
#else
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#endif

#include <iostream>

#include <GL/glew.h>
#include "main.hpp"
#include "vector3.hpp"
#include "sprite.hpp"

Captain captain;

namespace {
	Vector3 eye;
	Vector3 center;
}

Captain::Captain()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_WM_SetCaption("Captain", NULL);
    SDL_SetVideoMode(screenX, screenY, screenBPP, SDL_OPENGL |SDL_RESIZABLE);
    glewInit();
	start();
}

Captain::~Captain()
{
    SDL_Quit();
}

void Captain::start()
{
    delta = 0.0f;
	time = 0.0f;
	nextFPS = 1000;
	running = true;

	screenX = 800;
	screenY = 600;
	screenBPP = 32;
}

// Move this to a separate class
void Captain::handleEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
					case SDLK_ESCAPE:
						running = false;
				}
				break;
		}
	}
}

void Captain::render()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(65, screenX/screenY, 0.1, 20);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eye.x, eye.y, eye.z,
              center.x, center.y, center.z,
              0, 1, 0);
}

int main(int argc, char** argv)
{
	while (captain.running)
	{
		float time = 0.001f * SDL_GetTicks();
		captain.delta = time - captain.time;
		if (captain.delta > 0.5)
			captain.delta = 0;
		captain.time = time;
		
		if (SDL_GetTicks() > captain.nextFPS)
		{
			std::cout << "FPS: " << (1.0f/captain.delta) << std::endl;
			captain.nextFPS += 1000;
		}

		captain.handleEvents();
		SDL_GL_SwapBuffers();
	}

	std::cout << "Program exit point" << std::endl;
	return 0;
}