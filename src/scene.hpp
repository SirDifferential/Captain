#ifndef __SCENE_HPP_
#define __SCENE_HPP_

#include <boost/shared_ptr.hpp>
#include "menu.hpp"
#include "arena.hpp"

class Scene
{
private:
	boost::shared_ptr<Arena> arenaPtr;
	boost::shared_ptr<Menu> menuPtr;
	int sceneType;
public:
	Scene();
	Scene(boost::shared_ptr<Menu> m);
	Scene(boost::shared_ptr<Arena> a);
	~Scene();
	void operate();
};

#endif

