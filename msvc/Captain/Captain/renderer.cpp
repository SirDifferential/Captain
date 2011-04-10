#include "renderer.hpp"
#include <GL/glew.h>
#include "vector3.hpp"
#include "programManager.hpp"
#include "objectManager.hpp"
#include "stars.hpp"
#include "sprite.hpp"

Renderer renderer;

namespace {
	Vector3 eye;
	Vector3 center;
	Stars stars;
}

Renderer::Renderer()
{
	eye.x = 0;
	eye.y = 0;
	eye.z = 30;

	currentBackground.x = progmgr.getScreenX()>>1;
	currentBackground.y = progmgr.getScreenY()>>1;
	currentBackground.opacity = 1.0f;
}

Renderer::~Renderer()
{
}

void Renderer::changeBackground()
{
	currentBackground = arena.giveBackground();
}

void Renderer::changeBackground(std::string path)
{
	Sprite temp(path);
	currentBackground = path;
}

void Renderer::renderBase()
{
	glClearColor(0.2f,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(65, progmgr.getScreenX()/progmgr.getScreenY(), 0.1, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eye.x, eye.y, eye.z,
              center.x, center.y, center.z,
              0, 1, 0);
}

void Renderer::renderBackground()
{
	if (progmgr.getUseRandomBG())
	{
		stars.render();
	} else {
		currentBackground.renderScale(2.0f);
	}
}

void Renderer::renderObjects()
{
}

void Renderer::renderForeground()
{
}

void Renderer::render()
{
	renderBase();
	renderBackground();
	renderObjects();
	renderForeground();
}