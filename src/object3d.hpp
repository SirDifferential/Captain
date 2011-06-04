#ifndef __OBJECT3D_HPP_
#define __OBJECT3D_HPP_

#include <GL/glew.h>
#include <vector>
#include <string>

class Object3D
{
private:
	
	std::vector<double> vertices;
	std::vector<double> normals;
	std::vector<double> indices;
	
	int verticeCount;
	
public:
	Object3D();
	Object3D(std::string path);
	~Object3D();
	void loadModel(std::string path);
	void render();
};

#endif
