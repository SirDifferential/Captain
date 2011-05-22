#include "object3d.hpp"
#include "objLoader.hpp"

Object3D::Object3D()
{
}

Object3D::~Object3D()
{
}

void Object3D::loadModel(std::string path)
{
	std::vector<std::vector<double> > data;
	data = objectLoader.readObjectFile(path);
	verticeCount = data.size();
}
