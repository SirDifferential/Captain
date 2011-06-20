#ifndef __OBJECTMANAGER_HPP_
#define __OBJECTMANAGER_HPP_

#include <vector>
#include "ship.hpp"
#include "sprite.hpp"
#include "arena.hpp"
#include "text.hpp"
#include "stars.hpp"
#include "scene.hpp"
#include <vector>
#include <boost/shared_ptr.hpp>

class ObjectManager
{
private:
	std::vector<boost::shared_ptr<Scene> > sceneVector;
	std::vector<Ship> shipVector;
	std::vector<boost::shared_ptr<Text> > genericTexts;
	std::vector<boost::shared_ptr<Sprite> > backgroundSprites;
	boost::shared_ptr<Sprite> mainBackgroundPtr;
	boost::shared_ptr<Scene> currentScenePtr;
	
	int sceneNumber;
	bool arenaCreated;
public:
	ObjectManager();
	~ObjectManager();
	
	void doFirstScene();
	
	void update();
	void changeScene(int num);
	void render();
	void renderBackground();
	void renderHUD();
	void addNewGenericText(int w, int h, std::string, std::string fontPath, int fontSize, int locx, int locy);
	void addNewBGSprite(const std::string &filename);
	void changeMainBackground(std::string filename);
	
	void createNewArena();
	void removeArena();
	
	bool getArenaCreated() { return arenaCreated; }
};

extern ObjectManager objectmgr;

#endif
