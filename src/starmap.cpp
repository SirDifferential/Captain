#include "starmap.hpp"
#include "toolbox.hpp"
#include "stars.hpp"

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// A bit about this thing right here...                                 //
// This class is a starmap. It is mostly a std::map                     //
// that contains pointers to SpaceSector type objects                   //
// These sectors then contain graphics and other                        //
// things in them.                                                      //
//                                                                      //
// This class always checks if there                                    //
// is any universe left in the 8 bordering regions                      //
// as referenced to the player. Look at your numpad.                    //
// Really, do it now.                                                   //
//                                                                      //
// Got it? Good.                                                        //
//                                                                      //
// Imagine that the player ship is on button 5.                         //
// This class checks if there is any space generated                    //
// at button 7. If there isn't any, then it will be                     //
// generated, and boom we have more universe in our                     //
// space. This is done for 8 next, then for 9, then                     //
// for the middle for 4, 5, 6, and finally for bottom                   //
// row of 1, 2 and 3.                                                   //
//                                                                      //
// This is executed once every frame, after which all                   //
// the border regions are rendered. This way we can                     //
// have an infinite procedural universe without the                     //
// player ever seeing the borders of the game.                          //
//                                                                      //
// I mentioned that the starmap is made by a std::map.                  //
// To be more precise, it is:                                           //
// std::map<std::pair<int, int>, boost::shared_ptr<SpaceSector> >       //
// The map key is a pair of coordinates. These are, roughly, the        //
// coordinates in the 3D space (OpenGL coordinates) divided by 1000     //
// So there will be a new sector every 1000 OpenGL units. The           //
// map structure will then have pairs like (0,0), (1,0) and (15,10)     //
// for coordinates (0,0), (1000,0), (15 000, 10 000) etc.               //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

Starmap::Starmap()
{
    fprintf(stderr, "Starmap constructing\n");
}

Starmap::~Starmap()
{
    fprintf(stderr, "Starmap destructing\n");
}

void Starmap::checkBorders(Vector3 loc)
{
    // Save the coordinates, we need them for rendering anyway
    playerCoords = loc;

    top_left.first = (playerCoords.x - 1000)/1000;
    top_left.second = (playerCoords.y + 1000)/1000;
    top_middle.first = playerCoords.x/1000;
    top_middle.second = (playerCoords.y + 1000)/1000;
    top_right.first = (playerCoords.x + 1000)/1000;
    top_right.second = (playerCoords.y + 1000)/1000;

    middle_left.first = (playerCoords.x - 1000)/1000;
    middle_left.second = playerCoords.y/1000;
    center.first = playerCoords.x/1000;
    center.second = playerCoords.y/1000;
    middle_right.first = (playerCoords.x + 1000)/1000;
    middle_right.second = playerCoords.y/1000;

    bottom_left.first = (playerCoords.x - 1000)/1000;
    bottom_left.second = (playerCoords.y - 1000)/1000;
    bottom_middle.first = playerCoords.x/1000;
    bottom_middle.second = (playerCoords.y - 1000)/1000;
    bottom_right.first = (playerCoords.x + 1000)/1000;
    bottom_right.second = (playerCoords.y - 1000)/1000;
    
    // Top row
    checkSector(top_left);
    checkSector(top_middle);
    checkSector(top_right);

    // Middle row
    checkSector(middle_left);
    checkSector(center);
    checkSector(middle_right);

    // Bottom row
    checkSector(bottom_left);
    checkSector(bottom_middle);
    checkSector(bottom_right);

}
// Checks if there is a sector at desired coordinates and creates a new if not found
void Starmap::checkSector(std::pair<int, int> coordinatesToCheck)
{
    // Search the universe for this pair
    universeIter = universe.find(coordinatesToCheck);
    if (universeIter == universe.end())
    {
        fprintf(stderr, "Empty universe at: %d %d\n", coordinatesToCheck.first, coordinatesToCheck.second);
        Vector3 starCoords;
        starCoords.x = coordinatesToCheck.first*1000;
        starCoords.y = coordinatesToCheck.second*1000;
        boost::shared_ptr<SpaceSector> sectorPtr(new SpaceSector(coordinatesToCheck.first*1000, coordinatesToCheck.second*1000));
        std::string areaName = tbox.combineStringAndInts("Generated stars ", coordinatesToCheck.first*1000, coordinatesToCheck.second*1000);
        boost::shared_ptr<Stars> starsPtr(new Stars(areaName, 1000, 0.3, starCoords));
        sectorPtr->assignStars(starsPtr);
        universe[coordinatesToCheck] = sectorPtr;
    }
}

void Starmap::render()
{
    // Render 9 sectors, only those that are visible
    universe[top_left]->getStars()->render();
    universe[top_middle]->getStars()->render();
    universe[top_right]->getStars()->render();
    universe[middle_left]->getStars()->render();
    universe[center]->getStars()->render();
    universe[middle_right]->getStars()->render();
    universe[bottom_left]->getStars()->render();
    universe[bottom_middle]->getStars()->render();
    universe[bottom_right]->getStars()->render();
}
