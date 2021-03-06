#ifndef _MENU_HPP_
#define _MENU_HPP_

#include "text.hpp"
#include <vector>
#include <boost/shared_ptr.hpp>

class Menu
{
private:
    int id;
    std::vector<boost::shared_ptr<Text> > items;
    std::vector<boost::shared_ptr<Text> > additionalTexts;
    boost::shared_ptr<Text> cursor;
    int currentSelection;
    int step;
public:
    Menu();
    ~Menu();
    std::vector<std::string> buttons;
    void moveup();
    void movedown();
    void select();
    void update();
    void render();
};

#endif
