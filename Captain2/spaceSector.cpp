#include "spaceSector.hpp"

SpaceSector::SpaceSector(int x, int y)
{
    fprintf(stderr, "New sector constructing at coords: %d, %d\n", x, y);
    coord_x = x;
    coord_y = y;
}

SpaceSector::~SpaceSector()
{
}

void SpaceSector::assignStars(boost::shared_ptr<Stars> input)
{
    stars = input;
}
