#include "object3d.hpp"
#include "objLoader.hpp"
#include "renderer.hpp"

Object3D::Object3D()
{
}

Object3D::Object3D(std::string path)
{
	loadModel(path);
}

Object3D::~Object3D()
{
}

void Object3D::loadModel(std::string path)
{
	std::vector<std::vector<double> > data;
	data = objectLoader.readObjectFile(path);
	vertices = data.at(0);
	normals = data.at(1);
	indices = data.at(2);
	verticeCount = vertices.size();
}

void Object3D::render()
{
	renderer.renderVertexArray(vertices, normals, indices, verticeCount);
}
