#ifndef __SQUARE_HPP_
#define __SQUARE_HPP_

#include "component.hpp"
#include <vector>

class Square
{
private:
	std::vector<Component> components;
public:
	Square();
	~Square();

	void render();
};

#endif
