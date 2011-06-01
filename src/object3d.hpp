#ifndef __OBJECT3D_HPP_
#define __OBJECT3D_HPP_

#include <GL/glew.h>
#include <string>

class Object3D
{
private:
//	GLfloat vertices[somesize];
//	GLfloat normals[somesize];
//	GLubyte indices[somesize];
	
	int verticeCount;
	
public:
	Object3D();
	~Object3D();
	void loadModel(std::string path);
};

#endif
