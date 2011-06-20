#include "scene.hpp"

Scene::Scene()
{
}

Scene::~Scene()
{
}

// Assign a pointer pointing to the arena that this abstract class describes
Scene::Scene(boost::shared_ptr<Arena> a)
{
	sceneType = 1;
	arenaPtr = a;
}

// Assign a pointer pointing to the menu that this abstract class describes
Scene::Scene(boost::shared_ptr<Menu> m)
{
	sceneType = 2;
	menuPtr = m;
}

// This is what should be done during each loop of the program in this
// particular scene. It can be moving the ships and other objects, rendering
// some effect and destroying objects if the scene is a
// solar system ("an arena").
// It can mean moving up and down if the scene is a menu, going to sub-menus
// and changing the program settings if the scene is a menu.
void Scene::operate()
{
	// Using if-elseif here speeds up a bit
	if (sceneType == 1)	// An arena
	{
		arenaPtr->update();
		arenaPtr->render();
	} else if (sceneType == 2) // A menu
	{
		menuPtr->update();
		menuPtr->render();
	}
}

