#include "inputmanager.hpp"
#include "manager.hpp"
#include "menu.hpp"

#ifdef WIN32
#include <SDL.h>
#include <windows.h>
#else
#include <SDL/SDL.h>
#endif

Inputmanager inputmgr;

Inputmanager::Inputmanager()
{
    fprintf(stderr, "Inputmanager being hired...\n");
}

Inputmanager::~Inputmanager()
{
    fprintf(stderr, "Inputmanager being fired...\n");
}

void Inputmanager::checkInput()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
            case SDL_QUIT:
                manager.stop();
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        manager.stop();
                        break;
                }
                break;
        }
    }
}

void Inputmanager::checkMenuInput(Menu &menu)
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
			case SDL_QUIT:
				manager.stop();
				break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
					case SDLK_ESCAPE:
						manager.stop();
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
