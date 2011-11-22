#include "menu.hpp"
#include "opengl.hpp"
#include "text.hpp"
#include "inputmanager.hpp"
#include "manager.hpp"
#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr<Text> TextPtr;

Menu::Menu()
{
    fprintf(stderr, "Menu constructing\n");
	std::vector<std::string> entries;
	entries.push_back("Play game");
	entries.push_back("Options");
	entries.push_back("Help");
	entries.push_back("Quit");

	// Size of screen
    int width = manager.getOpengl()->getScreenX()/2;
	int height = manager.getOpengl()->getScreenY()/2-50;		// Leave 50 pixels of border
	
	// Size of text
	int sizex = 0;
	int sizey = 0;
	
	for (int i = 0; i < entries.size(); i++)
	{
		sizex = entries[i].length()*7;
		sizey = 12;
		TextPtr tempTextPtr(new Text(sizex, sizey, entries[i].c_str(), "data/fonts/ArcadeClassic.ttf", 50));
		items.push_back(tempTextPtr);
        fprintf(stderr, "Item %s added to the list\n", entries[i].c_str());
	}
	
	fprintf(stderr, "Creating logo\n");
	TextPtr tempTextPtr2(new Text(70, 20, "CAPTAIN", "data/fonts/BulwarkNF.ttf", 40)); 
	additionalTexts.push_back(tempTextPtr2);
	TextPtr tempTextPtr(new Text(10, 10, "O", "data/fonts/ArcadeClassic.ttf", 15));
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
	
	// Meh, let's just add this hack here
	currentSelection = 1;
	moveup();
    fprintf(stderr, "Menu constructed\n");
}

Menu::~Menu()
{
    fprintf(stderr, "Menu destructing\n");
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

void Menu::select()
{
	// Make stuff here for dynamic options
	if (currentSelection == 0)
	{
        manager.getRoomMgr()->nextRoom();
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
		manager.stop();
	}
	
}

void Menu::update()
{
}

void Menu::render()
{	
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
