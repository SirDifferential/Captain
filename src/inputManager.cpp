#include "inputManager.hpp"
#include "programManager.hpp"

#ifdef WIN32
#include <SDL.h>
#include <windows.h>
#else
#include <SDL/SDL.h>
#endif

#include <iostream>

InputManager inputmgr;

InputManager::InputManager()
{
	std::cout << "Creating InputManager" << std::endl;
}

InputManager::~InputManager()
{
}

void InputManager::handleInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
			case SDL_QUIT:
				progmgr.setRunning(false);
				break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
					case SDLK_ESCAPE:
						progmgr.setRunning(false);
				}
				break;
		}
	}
}