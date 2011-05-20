#ifndef __RENDERER_HPP_
#define __RENDERER_HPP_

#include "sprite.hpp"
#include <GL/glew.h>

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
	
	void renderTriangle(float *v1, float *v2, float *v3);
	void normalize(float v[3]);
	void normcrossprod(float v1[3], float v2[3], float out[3]);
	void renderVertexArray(GLfloat vertices[], GLubyte indices[], GLfloat normals[], GLfloat colors[], float rotation, int numberOfVertices);
};

extern Renderer renderer;

#endif
