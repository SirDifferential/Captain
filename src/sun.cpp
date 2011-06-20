#include "sun.hpp"
#include "programManager.hpp"
#include "renderer.hpp"

/*

GLfloat vertices[] = {1,1,1,  -1,1,1,  -1,-1,1,  1,-1,1,        // v0-v1-v2-v3
                      1,1,1,  1,-1,1,  1,-1,-1,  1,1,-1,        // v0-v3-v4-v5
                      1,1,1,  1,1,-1,  -1,1,-1,  -1,1,1,        // v0-v5-v6-v1
                      -1,1,1,  -1,1,-1,  -1,-1,-1,  -1,-1,1,    // v1-v6-v7-v2
                      -1,-1,-1,  1,-1,-1,  1,-1,1,  -1,-1,1,    // v7-v4-v3-v2
                      1,-1,-1,  -1,-1,-1,  -1,1,-1,  1,1,-1};   // v4-v7-v6-v5


GLfloat normals[] = {0,0,1,  0,0,1,  0,0,1,  0,0,1,             // v0-v1-v2-v3
                     1,0,0,  1,0,0,  1,0,0, 1,0,0,              // v0-v3-v4-v5
                     0,1,0,  0,1,0,  0,1,0, 0,1,0,              // v0-v5-v6-v1
                     -1,0,0,  -1,0,0, -1,0,0,  -1,0,0,          // v1-v6-v7-v2
                     0,-1,0,  0,-1,0,  0,-1,0,  0,-1,0,         // v7-v4-v3-v2
                     0,0,-1,  0,0,-1,  0,0,-1,  0,0,-1};        // v4-v7-v6-v5

// color array
GLfloat colors[] = {1,1,1,  1,1,0,  1,0,0,  1,0,1,              // v0-v1-v2-v3
                    1,1,1,  1,0,1,  0,0,1,  0,1,1,              // v0-v3-v4-v5
                    1,1,1,  0,1,1,  0,1,0,  1,1,0,              // v0-v5-v6-v1
                    1,1,0,  0,1,0,  0,0,0,  1,0,0,              // v1-v6-v7-v2
                    0,0,0,  0,0,1,  1,0,1,  1,0,0,              // v7-v4-v3-v2
                    0,0,1,  0,0,0,  0,1,0,  0,1,1};             // v4-v7-v6-v5

GLubyte indices[] = {0,1,2,3,
                     4,5,6,7,
                     8,9,10,11,
                     12,13,14,15,
                     16,17,18,19,
                     20,21,22,23};


*/

Sun::Sun()
{
}

// Construct a new sun, spooky. Params are mass, temperature, radius, location
Sun::Sun(int m, int t, int r, int posX, int posY)
{
	mass = m;
	temperature = t;
	position.x = posX;
	position.y = posY;
	position.z = -10;
	radius = r;
	colour.x = double(rand())/RAND_MAX;
	colour.y = double(rand())/RAND_MAX;
	colour.z = double(rand())/RAND_MAX;
	angle2 = 0.0f;
	position.y -= 5;
	position.x -= 5;
	
	boost::shared_ptr<Object3D> tempPtr(new Object3D("suzanne.obj"));
	modelPointer = tempPtr;
	modelPointer->setLocation(position);
	modelPointer->setRotation(angle2);
	position.y -= 5;
	
	std::cout << "=======" << std::endl;
	std::cout << "Created a new sun with following properties:" << std::endl;
	std::cout << "- mass: " << mass << std::endl;
	std::cout << "- temperature: " << temperature << std::endl;
	std::cout << "- radius: " << radius << std::endl;
	std::cout << "- position X: " << position.x << std::endl;
	std::cout << "- position Y: " << position.y << std::endl;
	std::cout << "=======" << std::endl;
}

Sun::~Sun()
{
}

// Render the sun by asking the model to render
void Sun::render()
{
	/*
	// Surely there is a better way to do this
	int numberOfVerts = sizeof(indices)/sizeof(indices[0]);
	//renderer.renderVertexArray(vertices, indices, normals, colors, angle2, numberOfVerts, 0.1f, position, colour);
	renderer.renderVertexArray(vertices, indices, normals, colors, angle2, numberOfVerts, 0.1f, position, colour);
	angle2 += 0.15f;
	if (angle2 > 360.0f)
		angle2 = 0.0f;
	*/
	modelPointer->render();
	angle2 += 0.15f;
	if (angle2 > 360.0f)
		angle2 = 0.0f;
	modelPointer->setRotation(angle2);
}

