#include "programManager.hpp"
#include "inputManager.hpp"
#include "renderer.hpp"
#include "timedFunctions.hpp"
#include <iostream>

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

#include <GL/glew.h>

ProgramManager progmgr;

ProgramManager::ProgramManager()
{
	std::cout << "Creating ProgramManager" << std::endl;
	start();
	std::cout << "SDL initializing" << std::endl;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_WM_SetCaption("Captain", NULL);
    SDL_SetVideoMode(screenX, screenY, screenBPP, SDL_OPENGL |SDL_RESIZABLE);
	std::cout << "OpenGL initializing" << std::endl;
    glewInit();
	std::cout << "progmgr created" << std::endl;
}

ProgramManager::~ProgramManager()
{
	SDL_Quit();
}

void ProgramManager::start()
{
	std::cout << "Setting up start-up variables" << std::endl;
    delta = 0.0f;
	gameTime = 0.0f;
	nextFPS = 1000;
	running = true;

	screenX = 1024;
	screenY = 768;
	screenBPP = 32;

	useRandomBG = false;
}

void ProgramManager::stop()
{
}

void ProgramManager::work()
{
	while (progmgr.running)
	{
		float time = 0.001f * SDL_GetTicks();
		delta = time - gameTime;
		if (delta > 0.5)
			delta = 0;
		gameTime = time;
		
		if (SDL_GetTicks() > nextFPS)
		{
			std::cout << "FPS: " << (1.0f/delta) << std::endl;
			nextFPS += 1000;
		}
		
		renderer.render();
		triggers.poll();

		inputmgr.handleInput();
		SDL_GL_SwapBuffers();
	}
}
