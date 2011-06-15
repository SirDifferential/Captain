#include "object3d.hpp"
#include "objLoader.hpp"
#include "renderer.hpp"
#include "toolbox.hpp"

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
	
	indices = tbox.doubleVectorToIntVector(data.at(2));
	
	verticeCount = vertices.size();
	indiceCount = indices.size();
	
	std::cout << "--------------------------------------" << std::endl;
	std::cout << "Object loaded: " << path << std::endl;
	std::cout << "Vertices: " << verticeCount << std::endl;
	std::cout << "Normals: " << normals.size() << std::endl;
	std::cout << "Indices: " << indiceCount << std::endl;
	std::cout << "--------------------------------------" << std::endl;
}
void Object3D::render()
{
	renderer.renderObject(GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, indices, vertices, normals);
}
