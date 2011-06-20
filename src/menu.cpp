#include "menu.hpp"
#include "programManager.hpp"
#include "objectManager.hpp"
#include "inputManager.hpp"
#include <iostream>

typedef boost::shared_ptr<Sprite> SpritePtr;
typedef boost::shared_ptr<Text> TextPtr;
typedef boost::shared_ptr<Stars> StarsPtr;
/*
This class does the main menu only at the moment. Parts of it
are prepared for all sorts of menus though, but for now it's
all hardcoded for the main menu
*/

Menu::Menu()
{
}

// Construct a list of Text Sprites. The param is a vector of strings, such as
// { "play game", "options", "exit" }
Menu::Menu(std::vector<std::string> entries, bool useStars)
{
	// Size of screen
	int width = progmgr.getScreenX()/2;
	int height = progmgr.getScreenY()/2-50;		// Leave 50 pixels of border
	
	// Size of text
	int sizex = 0;
	int sizey = 0;
	
	for (int i = 0; i < entries.size(); i++)
	{
		sizex = entries[i].length()*15;	// 7 pixels per character
		sizey = 25;			// 10 pixels high
		TextPtr tempTextPtr(new Text(sizex, sizey, entries[i].c_str(), "ArcadeClassic.ttf", 50));
		items.push_back(tempTextPtr);
		std::cout << "Item " << entries[i].c_str() << " added to the list" << std::endl;
	}
	
	std::cout << "Creating logo" << std::endl;
	TextPtr tempTextPtr2(new Text(300, 200, "CAPTAIN", "BulwarkNF.ttf", 70)); 
	additionalTexts.push_back(tempTextPtr2);
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
		(*iter)->x = width;		// Draw to center
		(*iter)->y = height - i*step;	// Draw with a good spacing
		i++;
	}
	
	// If we want background stars
	if (useStars)
		createMenuStars();
	
	// Meh, let's just add this hack here
	currentSelection = 1;
	moveup();
}

Menu::~Menu()
{
}

// Tell ObjectManager to render the possible background things for the menu,
// Then render each of the text elements
void Menu::render()
{
	if (backgroundStarsPtr != NULL)
		backgroundStarsPtr->render();
	
	// If there are additional graphics
	for (std::vector<TextPtr>::iterator iter = additionalTexts.begin(); iter!= additionalTexts.end(); iter++)
	{
		(*iter)->render();
	}
	
	for (std::vector<TextPtr>::iterator iter = items.begin(); iter != items.end(); iter++)
	{
		(*iter)->render();
	}
	
	cursor->render();
}

// Move the cursor up one slot
void Menu::moveup()
{
	currentSelection--;
	if (currentSelection < 0)
		currentSelection = items.size()-1;
	TextPtr tempTextPtr = items[currentSelection];
	cursor->y = tempTextPtr->y;
}

// Move the cursor down one slot
void Menu::movedown()
{
	currentSelection++;
	if (currentSelection > items.size()-1)
		currentSelection = 0;
	TextPtr tempTextPtr = items[currentSelection];
	cursor->y = tempTextPtr->y;
}

// The user has pressed enter, and the currently pointed option will be
// selected. Currently hard-coded for the main menu
void Menu::select()
{
	// Make stuff here for dynamic options
	if (currentSelection == 0)
	{
		objectmgr.createNewArena();
	}
	if (currentSelection == 1)
	{
		// Go to options
	}
	if (currentSelection == 2)
	{
		// Display help
	}
	if (currentSelection == 3)
	{
		progmgr.setRunning(false);
	}
	
}

// Create some stars to work as a background
void Menu::createMenuStars()
{
	StarsPtr tempPtr(new Stars());
	backgroundStarsPtr = tempPtr;
}

// Handle moving in the menu
void Menu::update()
{
	inputmgr.handleMenuInput(*this);
}

