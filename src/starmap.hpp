#ifndef _STARMAP_HPP_
#define _STARMAP_HPP_

#include "spaceSector.hpp"
#include "vector3.hpp"
#include <map>
#include <boost/shared_ptr.hpp>

class Starmap
{
private:
    int id;
    std::map<std::pair<int, int>, boost::shared_ptr<SpaceSector> > universe;
    std::map<std::pair<int, int>, boost::shared_ptr<SpaceSector> >::iterator universeIter;
    Vector3 playerCoords;   // Keeps track where the player is

    // coordinates of surrounding sectors
    std::pair<int, int> top_left;
    std::pair<int, int> top_middle;
    std::pair<int, int> top_right;
    std::pair<int, int> middle_left;
    std::pair<int, int> center;
    std::pair<int, int> middle_right;
    std::pair<int, int> bottom_left;
    std::pair<int, int> bottom_middle;
    std::pair<int, int> bottom_right;
public:
    Starmap();
    ~Starmap();

    void checkBorders(Vector3 playerLoc);
    void checkSector(std::pair<int, int> coords);
    void render();
};

#endif
