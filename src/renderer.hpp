#ifndef __RENDERER_HPP_
#define __RENDERER_HPP_

#include "sprite.hpp"

class Renderer
{
private:
	void renderBase();
	void renderBackground();
	void renderObjects();
	void renderForeground();

	Sprite currentBackground;
public:
	Renderer();
	~Renderer();
	void render();
	void changeBackground();
	void changeBackground(std::string path);
};

extern Renderer renderer;

#endif
