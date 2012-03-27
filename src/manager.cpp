#include "manager.hpp"
#include "opengl.hpp"
#include "renderer.hpp"
#include "inputmanager.hpp"
#include "audiomanager.hpp"
#include "roommanager.hpp"

Manager manager;

Manager::Manager()
{
    fprintf(stderr, "CEO hired (project development time +3 months, morale -2\n");
    debug = true;
    running = true;
    gameTime = 0.0f;
    openglPtr = boost::shared_ptr<Opengl>(new Opengl());
    if (!openglPtr->start())
        stop();
    roomManagerPtr = boost::shared_ptr<RoomManager>(new RoomManager());
    if (!roomManagerPtr->init())
        stop();
    audioManagerPtr = boost::shared_ptr<AudioManager>(new AudioManager());
    if (!audioManagerPtr->init())
        stop();
    audioManagerPtr->startMusic();
    physicsPtr = boost::shared_ptr<Physics>(new Physics());
    if (!physicsPtr->init())
        stop();
}

Manager::~Manager()
{
    fprintf(stderr, "CEO fired, project finished\n");
}

void Manager::stop()
{
    running = false;
}

int Manager::run()
{
    float time = openglPtr->giveTicks();
    nextFPS = time + 1000;
    fprintf(stderr, "Entering main loop\n");
    while (running)
    {
        time = 0.001f * openglPtr->giveTicks();
        float delta = time-gameTime;
        if (delta > 0.5)
            delta = 0;
        gameTime = time;

        if (openglPtr->giveTicks() > nextFPS && debug == true)
        {
            fprintf(stderr, "FPS: %f\n", (1.0f/delta));
            nextFPS += 1000;
        }

	inputmgr.resetKeys();
        inputmgr.checkInput();
        renderer.render();

        if (openglPtr->getLimitFPS() == 1)
        {
            // Limit the FPS
            while (delta < 1.0f/openglPtr->getFPS())
            {
                inputmgr.checkInput();
                delta = (0.001f*openglPtr->giveTicks())-time;
            }
        }
    }
    fprintf(stderr, "Manager exiting naturally\n");
    return 0;
}

void Manager::setParams(int input_argc, char** input_argv)
{
    argc = input_argc;
    argv = input_argv;
}

void Manager::getEnter()
{
#ifdef WIN32
    fprintf(stderr, "Press return to continue\n");
    std::cin.get();
#else
    fprintf(stderr, "Press any key + enter to continue");
    std::string dummystr;
    std::cin >> dummystr;
#endif
}
