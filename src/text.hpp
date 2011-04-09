#ifndef __TEXT_HPP_
#define __TEXT_HPP_

#include "sprite.hpp"

class Text : public Sprite
{
public:
	Text();
	Text(int x, int y, std::string);
	void render();
	void update(int offset);

	TTF_Font *font;
	SDL_Color textColor;

	float color1, color2, color3;
};

#endif
