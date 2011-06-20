#include "square.hpp"
#include "programManager.hpp"

Square::Square()
{
}

Square::~Square()
{
}

void Square::render()
{
	for (int i = 0; i < components.size(); i++)
	{
		Component &c = components[i];
		c.render();
	}
}
