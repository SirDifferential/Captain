#include "ship.hpp"
#include "programManager.hpp"

Ship::Ship()
{
	hull = Sprite("hull1.png");
}

Ship::~Ship()
{
}

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