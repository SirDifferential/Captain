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
    boost::shared_ptr<Room> currentRoom = manager.getRoomMgr()->giveCurrentRoom();
    if (currentRoom->getName().compare("Main menu") == 0)
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
					    case SDLK_UP:
                            currentRoom->giveMenu()->moveup();
						    break;
					    case SDLK_DOWN:
						    currentRoom->giveMenu()->movedown();
						    break;
					    case SDLK_RETURN:
						    currentRoom->giveMenu()->select();
						    break;
				    }
				    break;
		    }
        }
    } else if (currentRoom->getName().compare("Help") == 0)
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
                            manager.getRoomMgr()->changeRoom("Main menu");
                            break;
                    }
                    break;
            }
        }
    } else if (currentRoom->getType() == 3 || currentRoom->getType() == 4)  // cinematics / text
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
                            currentRoom->iterateSprites();
                            break;
                        case SDLK_RETURN:
                            currentRoom->iterateSprites();
                            break;
                    }
                    break;
            }
        }
    } else
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
}
