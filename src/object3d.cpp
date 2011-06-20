#include "object3d.hpp"
#include "objLoader.hpp"
#include "renderer.hpp"
#include "toolbox.hpp"

Object3D::Object3D()
{
}

// Create a new 3D Object by loading the data from a .obj file
Object3D::Object3D(std::string path)
{
	loadModel(path);
	scale = 1.0f;
}

Object3D::~Object3D()
{
}

// Call the Object Loader to load the .obj, then fill all the required
// fields. Naturally this consists of vertices, normals and indices.
// In future, include materials and animations, stuff like that
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

// Set the location to which the object is rendered
void Object3D::setLocation(Vector3 in)
{
	location = in;
}

// Set the rotation at which the object is rendered
void Object3D::setRotation(float in)
{
	rotation = in;
}

// Call the renderer with all our data
void Object3D::render()
{
	/*
	glShadeModel(GL_SMOOTH);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);
	glDisable(GL_LIGHTING);
	glColor4f(1,1,1,1);
	glLoadIdentity();
	glScalef(scale, scale, scale);
    glTranslatef(location.x, location.y, location.z);
    glRotatef(rotation, rotation, rotation, 1.0f);
	*/
	renderer.renderObject(GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, indices, vertices, normals, location, rotation, scale);
}

