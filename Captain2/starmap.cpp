#include "starmap.hpp"
#include "toolbox.hpp"
#include "stars.hpp"

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

    top_left.first = playerCoords.x - 1000;
    top_left.second = playerCoords.y + 1000;
    top_middle.first = playerCoords.x;
    top_middle.second = playerCoords.y + 1000;
    top_right.first = playerCoords.x + 1000;
    top_right.second = playerCoords.y + 1000;

    middle_left.first = playerCoords.x - 1000;
    middle_left.second = playerCoords.y;
    center.first = playerCoords.x;
    center.second = playerCoords.y;
    middle_right.first = playerCoords.x + 1000;
    middle_right.second = playerCoords.y;

    bottom_left.first = playerCoords.x - 1000;
    bottom_left.second = playerCoords.y - 1000;
    bottom_middle.first = playerCoords.x;
    bottom_middle.second = playerCoords.y - 1000;
    bottom_right.first = playerCoords.x + 1000;
    bottom_right.second = playerCoords.y - 1000;
    
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
    if (universe.find(coordinatesToCheck) == false)
    {
        fprintf(stderr, "Empty universe at: %d %d\n", coordinatesToCheck.first, coordinatesToCheck.second);
        Vector3 starCoords;
        starCoords.x = coordinatesToCheck.first;
        starCoords.y = coordinatesToCheck.second;
        boost::shared_ptr<SpaceSector> sectorPtr(new SpaceSector(coordinatesToCheck.first, coordinatesToCheck.second));
        std::string areaName = tbox.combineStringAndInts("Generated stars ", coordinatesToCheck.first, coordinatesToCheck.second);
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
