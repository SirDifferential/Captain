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

// Resets all keys as pressable at the beginning of the loop
void Inputmanager::resetKeys()
{
    triggeredLeft = false;
    triggeredRight = false;
    triggeredUp = false;
    triggeredDown = false;
    triggeredA = false;
    triggeredD = false;
    triggeredZ = false;
    triggeredX = false;
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
                            // Ehm, this is a bit ugly: change to currently active arena
                            manager.getRoomMgr()->changeRoom(manager.getRoomMgr()->giveArenaRoom()->getName());
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
    } else if (currentRoom->getType() == 3 || currentRoom->getType() == 1)  // Arena
    {
    /*triggeredLeft = false;
    triggeredRight = false;
    triggeredUp = false;
    triggeredDown = false;
    triggeredA = false;
    triggeredD = false;
    triggeredZ = false;
    triggeredX = false;*/
        Uint8* keystate = SDL_GetKeyState(NULL);
        if(keystate[SDLK_LEFT])
        {
            if (!triggeredLeft)
            {
                currentRoom->getPlayerShip()->rotateLeft();
                triggeredLeft = true;
            }
        }
        if(keystate[SDLK_RIGHT])
        {
            currentRoom->getPlayerShip()->rotateRight();
        }
        if(keystate[SDLK_UP])
        {
            currentRoom->getPlayerShip()->accelerate();
        }
        if(keystate[SDLK_DOWN])
        {
            currentRoom->getPlayerShip()->decelerate();
        }

        if(keystate[SDLK_a])
        {
            currentRoom->getPlayerShip()->strafeLeft();
        }

        if(keystate[SDLK_d])
        {
            currentRoom->getPlayerShip()->strafeRight();
        }

        if(keystate[SDLK_z])
        {
            currentRoom->getPlayerShip()->cameraZoomIn();
        }
        if(keystate[SDLK_x])
        {
            currentRoom->getPlayerShip()->cameraZoomOut();
        }
        if(keystate[SDLK_k])
        {
            currentRoom->getPlayerShip()->fireWeapon1();
        }

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
    } else if (currentRoom->getName().compare("Options") == 0)
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
					    case SDLK_UP:
                            currentRoom->giveOptions()->moveup();
						    break;
					    case SDLK_DOWN:
						    currentRoom->giveOptions()->movedown();
						    break;
					    case SDLK_RETURN:
						    currentRoom->giveOptions()->select();
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
