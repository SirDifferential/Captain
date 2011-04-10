#ifndef __ARENA_HPP_
#define __ARENA_HPP_

#include "sprite.hpp"

class Arena
{
private:
	Sprite background;
	void changeBackground();
public:
	Arena();
	Arena(std::string);
	~Arena();

	Sprite giveBackground() { return background; }
};

extern Arena arena;

#endif
