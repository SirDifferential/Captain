#ifndef _MANAGER_HPP_
#define _MANAGER_HPP_

#include <vector>
#include <boost/shared_ptr.hpp>
#include "audiomanager.hpp"
#include "roommanager.hpp"
#include "opengl.hpp"

class Manager
{
private:
    int id;
    int argc;
    char** argv;
    bool running;
    int nextFPS;
    float gameTime;
    bool debug;
    boost::shared_ptr<AudioManager> audioManagerPtr;
    boost::shared_ptr<RoomManager> roomManagerPtr;
    boost::shared_ptr<Opengl> openglPtr;
public:
    Manager();
    ~Manager();
    int run();
    void stop();
    void setParams(int argc, char** args);
    double getTime() { return gameTime; }
    void getEnter();
    boost::shared_ptr<AudioManager> getAudioMgr() { return audioManagerPtr; }
    boost::shared_ptr<RoomManager> getRoomMgr() { return roomManagerPtr; }
    boost::shared_ptr<Opengl> getOpengl() { return openglPtr; }
};

extern Manager manager;

#endif
