#ifndef __OBJECTMANAGER_HPP_
#define __OBJECTMANAGER_HPP_

#include <vector>
#include "ship.hpp"
#include "sprite.hpp"
#include "arena.hpp"
#include "text.hpp"
#include "stars.hpp"
#include <vector>
#include <boost/shared_ptr.hpp>

class ObjectManager
{
private:
	std::vector<Ship> shipVector;
	std::vector<boost::shared_ptr<Text> > genericTexts;
	std::vector<boost::shared_ptr<Text> > menuTexts;
	std::vector<boost::shared_ptr<Arena> > arenaList;
	std::vector<boost::shared_ptr<Sprite> > backgroundSprites;
	boost::shared_ptr<Stars> menuStarsPtr;
	boost::shared_ptr<Sprite> mainBackgroundPtr;
	boost::shared_ptr<Arena> currentArenaPtr;
	
	int roomNumber;
	bool arenaCreated;
public:
	ObjectManager();
	~ObjectManager();
	
	void render();
	void renderMenuStuff();
	void renderBackground();
	void addNewGenericText(int w, int h, std::string, std::string fontPath, int fontSize, int locx, int locy);
	void addNewMenuText(int w, int h, std::string, std::string fontPath, int fontSize, int locx, int locy);
	void addNewBGSprite(const std::string &filename);
	void changeMainBackground(std::string filename);
	
	void prepareArena();
	void removeArena();
	void updateArena();
	
	bool getArenaCreated() { return arenaCreated; }
};

extern ObjectManager objectmgr;

#endif
