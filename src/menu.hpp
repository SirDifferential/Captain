#ifndef __MENU_HPP_
#define __MENU_HPP_

#include "text.hpp"
#include <vector>
#include <boost/shared_ptr.hpp>

class Menu
{
private:
	std::vector<boost::shared_ptr<Text> > items;
	boost::shared_ptr<Text> cursor;
	
	int currentSelection;
	int step;
public:
	Menu();
	Menu(std::vector<std::string> entries);
	~Menu();
	
	void render();
	void moveup();
	void movedown();
	void select();
};

#endif
