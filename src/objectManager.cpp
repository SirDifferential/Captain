#include "objectManager.hpp"
#include "programManager.hpp"
#include "scene.hpp"

typedef boost::shared_ptr<Text> TextPtr;
typedef boost::shared_ptr<Sprite> SpritePtr;
typedef boost::shared_ptr<Stars> StarsPtr;
typedef boost::shared_ptr<Scene> ScenePtr;
typedef boost::shared_ptr<Menu> MenuPtr;
typedef boost::shared_ptr<Arena> ArenaPtr;
ObjectManager objectmgr;

// Construct our divine Object Manager. Set some "first loop variables"
// and generate some basic objects
ObjectManager::ObjectManager()
{
	sceneNumber = 0;
	arenaCreated = false;
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::doFirstScene()
{
	// Create the main menu, and make it the current scene
	// These need to be done elsewhere as opengl can't give ids yet
	std::vector<std::string> menuItems;
	menuItems.push_back("Play game");
	menuItems.push_back("Options");
	menuItems.push_back("Help");
	menuItems.push_back("Quit");
	std::cout << "Creating menu" << std::endl;
	// Construct a new menu with the boolean "true" for using bg stars
	MenuPtr tempMenuPtr(new Menu(menuItems, true));
	ScenePtr tempScenePtr(new Scene(tempMenuPtr));
	sceneVector.push_back(tempScenePtr);
	currentScenePtr = sceneVector.at(0);
	
	// Add something to work as the placeholder before loading anything real
	changeMainBackground("default.png");
	std::cout << "ObjectManager reports all ready" << std::endl;
}

// Call each of the object vectors, and ask the objects to render
void ObjectManager::render()
{
	for (int i = 0; i < shipVector.size(); i++)
	{
		Ship &s = shipVector[i];
		s.render();
	}
	
	for (std::vector<TextPtr>::iterator iter = genericTexts.begin(); iter != genericTexts.end(); iter++)
	{
		(*iter)->render();
	}
}

void ObjectManager::renderHUD()
{
}

// Create a new Text Sprite, then push it to the generic text vector
void ObjectManager::addNewGenericText(int w, int h, std::string message, std::string fontPath, int fontSize, int locx, int locy)
{
	TextPtr tempTextPtr(new Text(w, h, message.c_str(), fontPath, fontSize));
	tempTextPtr->x = locx;
	tempTextPtr->y = locy;
	genericTexts.push_back(tempTextPtr);
}

// Add a new Sprite, then push it into the background sprite vector
void ObjectManager::addNewBGSprite(const std::string &filename)
{
	SpritePtr tempSpritePtr(new Sprite(filename));
	backgroundSprites.push_back(tempSpritePtr);
}

// Change our current background by making the main background pointer to point
// to a new, freshly created background Sprite. Consider doing this by
// iterating in the background vector
void ObjectManager::changeMainBackground(std::string filename)
{
	SpritePtr tempSprite(new Sprite(filename));
	mainBackgroundPtr = tempSprite;
}

// For now, if we are in the menu, render the speed bg stars
// Else, render whatever is our current background
void ObjectManager::renderBackground()
{
	//mainBackgroundPtr->render();
}

void ObjectManager::createNewArena()
{
	ArenaPtr tempPtr(new Arena());
	ScenePtr tempPtr2(new Scene(tempPtr));
	sceneVector.push_back(tempPtr2);
	sceneNumber++;
	changeScene(sceneNumber);
	arenaCreated = true;
}

// Tell everyone that we don't have a current arena active
void ObjectManager::removeArena()
{
	arenaCreated = false;
}

// Change our current scene to something else
void ObjectManager::changeScene(int sceneNum)
{
	currentScenePtr = sceneVector.at(sceneNum);
}

// Call our current scene, whatever it may be, to update
void ObjectManager::update()
{
	currentScenePtr->operate();
}

