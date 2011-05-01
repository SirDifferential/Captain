#ifndef __OBJECTMANAGER_HPP_
#define __OBJECTMANAGER_HPP_

#include <vector>
#include "ship.hpp"
#include "sprite.hpp"
#include "arena.hpp"
#include "text.hpp"
#include <vector>
#include <boost/shared_ptr.hpp>

class ObjectManager
{
private:
	std::vector<Ship> shipVector;
	std::vector<boost::shared_ptr<Text> > genericTexts;
	std::vector<boost::shared_ptr<Arena> > arenaList;
	std::vector<boost::shared_ptr<Sprite> > backgroundSprites;
	boost::shared_ptr<Sprite> mainBackgroundPtr;
public:
	ObjectManager();
	~ObjectManager();

	void render();
	void renderBackground();
	void addNewGenericText(int w, int h, std::string);
	void addNewBGSprite(const std::string &filename);
	void changeMainBackground(std::string filename);
};

extern ObjectManager objectmgr;

#endif
