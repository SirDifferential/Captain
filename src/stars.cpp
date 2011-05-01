#include <GL/glew.h>
#include "stars.hpp"
#include "programManager.hpp"
#include <ctime>
#include <cstdlib>

float distanceTo(float loc, float target)
{
	float out = 0.0f;
	out = target-loc;
	return out;
}

Stars::Stars()
{
	opacity = 1;
	stars.reserve(10000);
	for (int i=0; i<10000; i++)
		stars.push_back(Star(this));
	for (std::vector<Star>::iterator i=stars.begin(); i!=stars.end(); ++i) {
		i->position.x = (double(rand())/RAND_MAX);
		i->position.y = (double(rand())/RAND_MAX);
		i->position.z = (double(rand())/RAND_MAX)*-1;
		i->position.x *= 1300;
		i->position.y *= 1300;
		i->color.x = 1.0-(double(rand())/RAND_MAX) * 0.4 + 0.3;
		i->color.y = 1.0-(double(rand())/RAND_MAX) * 0.4 + 0.2;
		i->color.z = 1.0-(double(rand())/RAND_MAX) * 0.4 + 0.1;
		i->size = rand() % 3 + 1;
		i->acceleration.z  = 0.0;
		i->firstChaotic = true;
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
	glEnable(GL_POINT_SMOOTH);
	
	glBegin(GL_POINTS);
	for (unsigned int i = 0; i < stars.size(); i++)
	{
		glPointSize(stars[i].size);
		stars[i].render();
	}
	glEnd();
}

void Stars::update()
{
	
	for (unsigned int i = 0; i < stars.size(); i++)
	{
		stars[i].update();
	}
}

void Stars::Star::render()
{
	glColor4f(color.x, color.y, color.z, stars->opacity);
	glVertex3fv(&position.x);
}

void Stars::Star::update()
{
	/*
	// Send all particles  towards (0, 0)
	acceleration.x = distanceTo(position.x, 0)/10000000;
	acceleration.y = distanceTo(position.y, 0)/10000000;
	velocity.x = velocity.x + acceleration.x;
	velocity.y = velocity.y + acceleration.y;
	position.x = position.x + velocity.x;
	position.y = position.y + velocity.y;
	*/

	// Blow up
	if (firstChaotic)
	{
		acceleration.x = double(rand())/RAND_MAX;
		acceleration.y = double(rand())/RAND_MAX;
		
		if (double(rand())/RAND_MAX > 0.5)
			acceleration.x = acceleration.x * -1;
		
		acceleration.x = acceleration.x/1000;
			
		if (double(rand())/RAND_MAX > 0.5)
			acceleration.y = acceleration.y * -1;
		
		acceleration.y = acceleration.y/1000;
		firstChaotic = false;
		
		velocity.x = 0;
		velocity.y = 0;
	} else {
		velocity.x = velocity.x + acceleration.x;
		velocity.y = velocity.y + acceleration.y;
		position.x = position.x + velocity.x;
		position.y = position.y + velocity.y;
	}
}
