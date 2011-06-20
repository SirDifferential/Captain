#ifndef __OBJECT3D_HPP_
#define __OBJECT3D_HPP_

#include <GL/glew.h>
#include <vector>
#include <string>
#include "vector3.hpp"

class Object3D
{
private:
	
	std::vector<double> vertices;
	std::vector<double> normals;
	std::vector<int> indices;
	
	int verticeCount;
	int indiceCount;
	Vector3 location;
	float rotation;
	float scale;
	
public:
	Object3D();
	Object3D(std::string path);
	~Object3D();
	void loadModel(std::string path);
	void render();
	
	void setLocation(Vector3 in);
	void setRotation(float in);
};

#endif

