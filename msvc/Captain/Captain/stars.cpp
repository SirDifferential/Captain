#include <GL/glew.h>
#include "stars.hpp"

Stars::Stars()
{
	opacity = 1;
	stars.reserve(10000);
	for (int i=0; i<10000; i++)
		stars.push_back(Star(this));
	for (std::vector<Star>::iterator i=stars.begin(); i!=stars.end(); ++i) {
		i->position.x = double(rand())/RAND_MAX*10;
		i->position.y = double(rand())/RAND_MAX*10;
		i->position.z = -5;
		i->position *= 200;
		i->position -= Vector3(100, 100, 100);
		i->color.x = (double(rand())/RAND_MAX) * 0.4 + 0.6;
		i->color.y = (double(rand())/RAND_MAX) * 0.3 + 0.7;
		i->color.z = (double(rand())/RAND_MAX) * 0.2 + 0.8;
		i->size = rand() % 3 + 1;
	}
}

Stars::~Stars()
{
}

Stars::Star::Star(Stars *stars)
{
	this->stars = stars;
}


void Stars::render()
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glPointSize(1);
	glBegin(GL_POINTS);
	for (unsigned int i = 0; i < stars.size()/4*3; i++)
	{
		stars[i].render();
	}
	glEnd();
	glPointSize(3);
	glBegin(GL_POINTS);
	for (unsigned int i = stars.size()/4*3; i < stars.size(); i++)
	{
		stars[i].render();
	}
	glEnd();
}

void Stars::Star::render()
{
	glColor4f(color.x, color.y, color.z, stars->opacity);
	glVertex3fv(&position.x);
}

