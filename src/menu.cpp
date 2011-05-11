#include "menu.hpp"
#include "programManager.hpp"
#include "objectManager.hpp"
#include <iostream>

typedef boost::shared_ptr<Text> TextPtr;

/*
This class does the main menu only at the moment. Parts of it
are prepared for all sorts of menus though, but for now it's
all hardcoded for the main menu
*/

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
	
	// Add texts into objectmgr TextPtr vector
	for (int i = 0; i < entries.size(); i++)
	{
		sizex = entries[i].length()*15;		// 7 pixels per character
		sizey = 25;							// 10 pixels high
		TextPtr tempSpritePtr(new Text(sizex, sizey, entries[i].c_str(), "ArcadeClassic.ttf", 50));
		items.push_back(tempSpritePtr);
		std::cout << "Item " << entries[i].c_str() << " added to the list" << std::endl;
	}
	
	std::cout << "Creating logo" << std::endl;
	objectmgr.addNewMenuText(300, 200, "CAPTAIN", "BulwarkNF.ttf", 70, progmgr.getScreenX()/2, progmgr.getScreenY()-250);
	TextPtr tempTextPtr(new Text(10, 10, "0", "ArcadeClassic.ttf", 30));
	cursor = tempTextPtr;
	
	assert(items.size() != 0);
	step = height/items.size();
	if (step > 40)
		step = 40;
	
	int posy = height;
	int i = 0;
	
	cursor->x = width-170;
	cursor->y = height-step;
	
	for (std::vector<TextPtr>::iterator iter = items.begin(); iter != items.end(); iter++)
	{
		(*iter)->x = width;				// Draw to center
		(*iter)->y = height - i*step;	// Draw with a good spacing
		i++;
	}
	
	// Meh, let's just add this hack here
	currentSelection = 1;
	moveup();
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
	
	cursor->render();
}

void Menu::moveup()
{
	currentSelection--;
	if (currentSelection < 0)
		currentSelection = items.size()-1;
	TextPtr tempTextPtr = items[currentSelection];
	cursor->y = tempTextPtr->y;
}

void Menu::movedown()
{
	currentSelection++;
	if (currentSelection > items.size()-1)
		currentSelection = 0;
	TextPtr tempTextPtr = items[currentSelection];
	cursor->y = tempTextPtr->y;
}

void Menu::select()
{
	// Make stuff here for dynamic options
	if (currentSelection == 0)
	{
		progmgr.setInMenu(false);
		progmgr.setInGame(true);
	}
	if (currentSelection == 1)
	{
		progmgr.setInMenu(false);
		progmgr.setInOptions(true);
	}
	if (currentSelection == 2)
	{
		progmgr.setInMenu(false);
		progmgr.setInHelp(true);
	}
	if (currentSelection == 3)
	{
		progmgr.setRunning(false);
	}
	
}
