#ifndef _OPTIONS_HPP_
#define _OPTIONS_HPP_

#include <boost/shared_ptr.hpp>
#include <vector>

class Text;

class Options
{
private:
    int id;
    std::vector<boost::shared_ptr<Text> > items;
    std::vector<boost::shared_ptr<Text> > additionalTexts;
    boost::shared_ptr<Text> cursor;
    int currentSelection;
    int step;
public:
    Options();
    ~Options();
    std::vector<std::string> buttons;
    void moveup();
    void movedown();
    void select();
    void update();
    void render();
};

#endif
