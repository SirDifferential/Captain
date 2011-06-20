#include "ship.hpp"
#include "programManager.hpp"

// Construct a new ship using the default placeholder hull design
Ship::Ship()
{
	hull = Sprite("hull1.png");
}

Ship::~Ship()
{
}

// Render the ship by asking each of the squares that make the ship to
// render themselves. This is a mess, really. It goes down all the way to
// the component level.
void Ship::render()
{
	// Render hull
	hull.render();
	
	// Render contents
	for (int i = 0; i < squares.size(); i++)
	{
		Square &s = squares[i];
		s.render();
	}
}

