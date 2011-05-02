#include "programManager.hpp"
#include "inputManager.hpp"
#include "objectManager.hpp"
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

static Mix_Music *music;

ProgramManager::ProgramManager()
{
	std::cout << "Creating ProgramManager" << std::endl;
	start();
	std::cout << "SDL initializing" << std::endl;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_WM_SetCaption("Captain", NULL);
	std::cout << "SDL_TTF initializing" << std::endl;
	TTF_Init();
#ifndef NOMUSIC
	std::cout << "Playing music" << std::endl;
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512);
	music = Mix_LoadMUS("captain_tune.ogg");
	Mix_PlayMusic(music, 5);
	Mix_VolumeMusic(SDL_MIX_MAXVOLUME);
#endif
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

	useRandomBG = true;
	inMenu = true;
	firstTime = true;
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
		
		// Some textures need to be created in the rendering loop
		if (firstTime)
		{
			std::vector<std::string> menuItems;
			menuItems.push_back("Play game");
			menuItems.push_back("Options");
			menuItems.push_back("Help");
			menuItems.push_back("Quit");
			std::cout << "Creating menu" << std::endl;
			mainMenu = Menu(menuItems);
			
			std::cout << "Creating logo" << std::endl;
			objectmgr.addNewGenericText(300, 200, "CAPTAIN", "BulwarkNF.ttf", 70, progmgr.getScreenX()/2, progmgr.getScreenY()-250);

			objectmgr.changeMainBackground("default.png");
			firstTime = false;
			std::cout << "First loop variable setup done" << std::endl;
		}
		
		renderer.render();
		if (inMenu)
		{
			mainMenu.render();
		}
		triggers.poll();

		inputmgr.handleInput();
		SDL_GL_SwapBuffers();
	}
}
