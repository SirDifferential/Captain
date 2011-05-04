#include "menu.hpp"
#include "programManager.hpp"
#include "objectManager.hpp"

typedef boost::shared_ptr<Text> TextPtr;

Menu::Menu()
{
}

Menu::Menu(std::vector<std::string> entries)
{
	// Size of screen
	int width = progmgr.getScreenX()/2;
	int height = progmgr.getScreenY()/2-50;		// Leave 50 pixels of border
	
	// Size of text
	int sizex = 0;
	int sizey = 0;
	
	for (int i = 0; i < entries.size(); i++)
	{
		sizex = entries[i].length()*15;		// 7 pixels per character
		sizey = 25;							// 10 pixels high
		TextPtr tempSpritePtr(new Text(sizex, sizey, entries[i].c_str(), "ArcadeClassic.ttf", 50));
		items.push_back(tempSpritePtr);
		std::cout << "Item " << entries[i].c_str() << " added to the list" << std::endl;
	}
	
	assert(items.size() != 0);
	int step = height/items.size();
	if (step > 40)
		step = 40;
	
	int posy = height;
	int i = 0;
	for (std::vector<TextPtr>::iterator iter = items.begin(); iter != items.end(); iter++)
	{
		(*iter)->x = width;				// Draw to center
		//(*iter)->y = height + i*step;	// Draw with good spacing
		(*iter)->y = height - i*step;
		i++;
	}
}

Menu::~Menu()
{
}

void Menu::render()
{
	objectmgr.renderMenuStuff();
	
	for (std::vector<TextPtr>::iterator iter = items.begin(); iter != items.end(); iter++)
	{
		(*iter)->render();
	}
}
