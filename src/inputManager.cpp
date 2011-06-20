// Gets key presses, all SDL

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

// Construct the singleton that records key presses.
// It's all SDL
InputManager::InputManager()
{
	std::cout << "Creating InputManager" << std::endl;
}

InputManager::~InputManager()
{
}

// Read the input from the event structure
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

void InputManager::handleMenuInput(Menu &menu)
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
						break;
					case SDLK_UP:
						menu.moveup();
						break;
					case SDLK_DOWN:
						menu.movedown();
						break;
					case SDLK_RETURN:
						menu.select();
						break;
				}
				break;
		}
	}
}

