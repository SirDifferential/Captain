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
public:
	Renderer();
	~Renderer();
	void render();
};

extern Renderer renderer;

#endif
