#ifndef __MENU_HPP_
#define __MENU_HPP_

#include "text.hpp"
#include "stars.hpp"
#include <vector>
#include <boost/shared_ptr.hpp>

class Menu
{
private:
	std::vector<boost::shared_ptr<Text> > items;
	std::vector<boost::shared_ptr<Text> > additionalTexts;
	boost::shared_ptr<Text> cursor;
	
	int currentSelection;
	int step;
	boost::shared_ptr<Stars> backgroundStarsPtr;
public:
	Menu();
	Menu(std::vector<std::string> entries, bool useStars);
	~Menu();

	void update();	
	void createMenuStars();
	void render();
	void moveup();
	void movedown();
	void select();
};

#endif
