#ifndef __RENDERER_HPP_
#define __RENDERER_HPP_

#include "sprite.hpp"
#include <GL/glew.h>
#include "vector3.hpp"

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
	
	void renderLamps();

	void renderTriangle(float *v1, float *v2, float *v3);
	void normalize(float v[3]);
	void normcrossprod(float v1[3], float v2[3], float out[3]);
	void renderVertexArray(GLfloat vertices[], GLubyte indices[], GLfloat colors[], GLfloat normals[], float rotation, int numberOfVertices, float scale, Vector3 trans, Vector3 colour);
	void renderVertexArray(std::vector<double> vertices, std::vector<double> normals, std::vector<double> indices, int numberOfVertices);
	void renderObject(GLenum primitiveType, int indiceCount, GLenum datatype, std::vector<double> indices, std::vector<double> vertices, std::vector<double> normals);
};

extern Renderer renderer;

#endif
