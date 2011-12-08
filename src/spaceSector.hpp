#ifndef _SPACESECTOR_HPP_
#define _SPACESECTOR_HPP_

#include <boost/shared_ptr.hpp>

class Stars;

class SpaceSector
{
private:
    int id;
    int coord_x;
    int coord_y;
    boost::shared_ptr<Stars> stars; // stars that occupy this sector
public:
    SpaceSector(int x, int y);
    ~SpaceSector();

    void assignStars(boost::shared_ptr<Stars> input);
    boost::shared_ptr<Stars> getStars() { return stars; }
};

#endif
