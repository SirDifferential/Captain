#include "sun.hpp"
#include "programManager.hpp"
#include <GL/glut.h>

Sun::Sun()
{
}

Sun::Sun(int m, int t, int r, int posX, int posY)
{
	mass = m;
	temperature = t;
	position.x = posX;
	position.y = posY;
	radius = r;
	
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

void Sun::render()
{
	glShadeModel(GL_FLAT);
	glColor3f(1.0, 0.0, 1.0);
	glLoadIdentity();
	glScalef(1.0, 1.0, 1.0);
	glEnable(GL_LIGHTING);
	glutSolidSphere(0.4, 8, 8);
}
