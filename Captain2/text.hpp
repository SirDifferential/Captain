#ifndef __TEXT_HPP_
#define __TEXT_HPP_

#include "sprite.hpp"
#ifdef WIN32
#include <SDL_ttf.h>
#else
#include <SDL/SDL_ttf.h>
#endif

class Text : public Sprite
{
private:
    Sprite textSprite;
	TTF_Font *font;
	SDL_Color textColor;
	float color1, color2, color3;
public:
	Text();
	Text(int x, int y, std::string, std::string fontPath, int fontSize);
	void render();
	void update(int offset);

};

#endif
