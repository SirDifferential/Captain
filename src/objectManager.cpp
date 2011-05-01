#include "objectManager.hpp"
#include "programManager.hpp"

typedef boost::shared_ptr<Text> TextPtr;
typedef boost::shared_ptr<Sprite> SpritePtr;

ObjectManager objectmgr;

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

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

void ObjectManager::addNewGenericText(int w, int h, std::string message)
{
	TextPtr tempTextPtr(new Text(w, h, message.c_str()));
	genericTexts.push_back(tempTextPtr);
}

void ObjectManager::addNewBGSprite(const std::string &filename)
{
	SpritePtr tempSpritePtr(new Sprite(filename));
	backgroundSprites.push_back(tempSpritePtr);
}

void ObjectManager::changeMainBackground(std::string filename)
{
	SpritePtr tempSprite(new Sprite(filename));
	mainBackgroundPtr = tempSprite;
}

void ObjectManager::renderBackground()
{
	mainBackgroundPtr->render();
}
