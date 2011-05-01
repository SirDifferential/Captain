#ifndef __PROGRAMMANAGER_HPP_
#define __PROGRAMMANGER_HPP_

#include "text.hpp"
#include "menu.hpp"

class ProgramManager
{
private:
	bool running;
	float gameTime;
	float delta;
	int nextFPS;
	int screenX;
	int screenY;
	int screenBPP;
	bool useRandomBG;
	bool inMenu;
	bool firstTime;

	Text logo;
	Menu mainMenu;
public:
	ProgramManager();
	~ProgramManager();

	void start();
	void stop();
	void work();

	float getTime() { return gameTime; }
	float getDelta() { return delta; }
	int getScreenX() { return screenX; }
	int getScreenY() { return screenY; }
	void setRunning(bool r) { running = r; }
	bool getUseRandomBG() { return useRandomBG; }
};

extern ProgramManager progmgr;

#endif
