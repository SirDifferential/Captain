#include "renderer.hpp"
#include <GL/glew.h>
#include "vector3.hpp"
#include "programManager.hpp"

namespace {
	Vector3 eye;
	Vector3 center;
}

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::renderBase()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(65, progmgr.getScreenX()/progmgr.getScreenY(), 0.1, 20);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eye.x, eye.y, eye.z,
              center.x, center.y, center.z,
              0, 1, 0);
}

void Renderer::render()
{
	renderBase();
}