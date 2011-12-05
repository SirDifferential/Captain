#ifndef _TEXT_HPP_
#define _TEXT_HPP_

#include "sprite.hpp"
#include "vector3.hpp"
#ifdef WIN32
#include <SDL_ttf.h>
#else
#include <SDL/SDL_ttf.h>
#endif

class Text : public Sprite
{
private:
	TTF_Font *font;
	SDL_Color textColor;
	Vector3 color;
public:
	Text();
	Text(int x, int y, std::string, std::string fontPath, int fontSize);
	void render();
	void update(int offset);

    void setColorR(float f);
    void setColorG(float f);
    void setColorB(float f);
    float getColorR() { return color.x; }
    float getColorG() { return color.y; }
    float getColorB() { return color.z; }

};

#endif
