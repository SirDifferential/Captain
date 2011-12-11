#include "options.hpp"
#include "manager.hpp"

typedef boost::shared_ptr<Text> TextPtr;

Options::Options()
{
    fprintf(stderr, "Options constructing\n");
	std::vector<std::string> entries;
    entries.push_back("Auto zoom");
    entries.push_back("empty");
    entries.push_back("empty");
	entries.push_back("Return");

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
	TextPtr tempTextPtr2(new Text(280, 80, "Options", "data/fonts/BulwarkNF.ttf", 80));
    tempTextPtr2->x = 300;
    tempTextPtr2->y = 450;
	additionalTexts.push_back(tempTextPtr2);
    tempTextPtr2 = TextPtr(new Text(20, 10, "On", "data/fonts/ArcadeClassic.ttf", 50));
    tempTextPtr2->x = width+130;
    tempTextPtr2->y = height;
    additionalTexts.push_back(tempTextPtr2);
    tempTextPtr2 = TextPtr(new Text(20, 10, "Off", "data/fonts/ArcadeClassic.ttf", 50));
    tempTextPtr2->x = width+130;
    tempTextPtr2->y = height;
    additionalTexts.push_back(tempTextPtr2);
	TextPtr tempTextPtr(new Text(10, 10, "O", "data/fonts/ArcadeClassic.ttf", 15));
	cursor = tempTextPtr;
	
	assert(items.size() != 0);
	step = height/items.size();
	if (step > 40)
		step = 40;
	
	int posy = height;
	int i = 0;
	
	cursor->x = width-120;
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
    fprintf(stderr, "Options constructed\n");
}

Options::~Options()
{
    fprintf(stderr, "Options destructing\n");
}

// Move the cursor up one slot
void Options::moveup()
{
	currentSelection--;
	if (currentSelection < 0)
		currentSelection = items.size()-1;
	TextPtr tempTextPtr = items[currentSelection];
	cursor->y = tempTextPtr->y;
}

// Move the cursor down one slot
void Options::movedown()
{
	currentSelection++;
	if (currentSelection > items.size()-1)
		currentSelection = 0;
	TextPtr tempTextPtr = items[currentSelection];
	cursor->y = tempTextPtr->y;
}

void Options::select()
{
	// Make stuff here for dynamic options
	if (currentSelection == 0)
	{
        boost::shared_ptr<Room> arenaRoom = manager.getRoomMgr()->giveArenaRoom();
        if (arenaRoom->getPlayerShip()->getUseAutoZoom() == false)
            arenaRoom->getPlayerShip()->setUseAutoZoom(true);
        else
            arenaRoom->getPlayerShip()->setUseAutoZoom(false);
	}
	if (currentSelection == 1)
	{
		fprintf(stderr, "Nothing implemented\n");
	}
	if (currentSelection == 2)
	{
        fprintf(stderr, "Nothing implemented\n");
	}
	if (currentSelection == 3)
	{
		manager.getRoomMgr()->changeRoom("Main menu");
	}
	
}

void Options::update()
{
}

void Options::render()
{	
    boost::shared_ptr<Room> arenaRoom = manager.getRoomMgr()->giveArenaRoom();
    

	for (std::vector<TextPtr>::iterator iter = additionalTexts.begin(); iter!= additionalTexts.end(); iter++)
	{
        if ((*iter)->getContent().compare("On") == 0 && (arenaRoom->getPlayerShip()->getUseAutoZoom() == true))
        {
            (*iter)->render();
        } else if ((*iter)->getContent().compare("Off") == 0 && (arenaRoom->getPlayerShip()->getUseAutoZoom() == false))
        {
            (*iter)->render();
        } else if ((*iter)->getContent().compare("On") == 1 && (*iter)->getContent().compare("Off") == 1)
        {
            (*iter)->setColorR(abs(sin(manager.getTime()*0.9)));
            (*iter)->setColorG(abs(cos(manager.getTime()*0.75)));
            (*iter)->setColorB(abs(cos(manager.getTime()*0.5)));
		    (*iter)->render();
        }
	}
	
	for (std::vector<TextPtr>::iterator iter = items.begin(); iter != items.end(); iter++)
	{
		(*iter)->render();
	}
	
	cursor->render();
}
