#include <GL/glew.h>
#include "stars.hpp"
#include "programManager.hpp"
#include <ctime>
#include <cstdlib>

// Returns the distance between two points
float distanceTo(float loc, float target)
{
	float out = 0.0f;
	out = target-loc;
	return out;
}

// Constructs a new field of stars. This is a a vector of Star-objects
Stars::Stars()
{
	opacity = 1;
	useSpeed = true;
	stars.reserve(10000);
	for (int i=0; i<10000; i++)
		stars.push_back(Star(this));
	for (std::vector<Star>::iterator i=stars.begin(); i!=stars.end(); ++i) {
		i->position.x = (double(rand())/RAND_MAX);
		i->position.y = (double(rand())/RAND_MAX);
		i->position.z = (double(rand())/RAND_MAX)*-1;
		i->position.x *= 1300;
		i->position.x += 1000;
		i->position.y *= 1300;
		i->color.x = 1.0-(double(rand())/RAND_MAX) * 0.4 + 0.3;
		i->color.y = 1.0-(double(rand())/RAND_MAX) * 0.4 + 0.2;
		i->color.z = 1.0-(double(rand())/RAND_MAX) * 0.4 + 0.1;
		i->size = rand() % 3 + 1;
		i->velocity.x = -1.6;
		i->velocity.y = (double(rand())/RAND_MAX)*-1*0.05;
		i->firstChaotic = true;
	}
}

// Same as above, but each star gets some acceleration
Stars::Stars(bool speed)
{
	useSpeed = speed;
	opacity = 1;
	stars.reserve(10000);
	for (int i=0; i<10000; i++)
		stars.push_back(Star(this));
	for (std::vector<Star>::iterator i=stars.begin(); i!=stars.end(); ++i) {
		i->position.x = (double(rand())/RAND_MAX);
		i->position.y = (double(rand())/RAND_MAX);
		i->position.z = (double(rand())/RAND_MAX)*-1;
		i->position.x *= 5000;
		i->position.x += 50;
		i->position.y *= 5000;
		i->color.x = 1.0-(double(rand())/RAND_MAX) * 0.4 + 0.3;
		i->color.y = 1.0-(double(rand())/RAND_MAX) * 0.4 + 0.2;
		i->color.z = 1.0-(double(rand())/RAND_MAX) * 0.4 + 0.1;
		i->size = rand() % 3 + 1;
		i->velocity.x = -1.6;
		i->velocity.y = (double(rand())/RAND_MAX)*-1*0.05;
		i->firstChaotic = true;
	}
}

Stars::~Stars()
{
}

// This cryptic play on words assigns the main stars vector as the residence
// for this single, lonely star so that it isn't alone anymore 
Stars::Star::Star(Stars *stars)
{
	this->stars = stars;
}

// The "upper" render function. Renders the stars in the stars vector
void Stars::render()
{
	if (useSpeed)
		update();
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

// If some sort of updating is needed (such as colour changes or movement),
// do it here
void Stars::update()
{
	// Update the individual stars. Do note that if there are thousands
	// of them, then this will take a long time	
	for (unsigned int i = 0; i < stars.size(); i++)
	{
		stars[i].update();
	}
}

// The "lower" render function. Renders a single dot into the 3D space
// Called from the "upper" render function, Stars::render()
void Stars::Star::render()
{
	glColor4f(color.x, color.y, color.z, stars->opacity);
	glVertex3fv(&position.x);
}

// If an individual star needs to be updated, do it here.
// Warning: Doing this for all the stars takes a lot of CPU
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
		/*
		acceleration.x = double(rand())/RAND_MAX;
		acceleration.y = double(rand())/RAND_MAX;
		
		if (double(rand())/RAND_MAX > 0.5)
			acceleration.x = acceleration.x * -1;
		
		acceleration.x = acceleration.x/1000;
			
		if (double(rand())/RAND_MAX > 0.5)
			acceleration.y = acceleration.y * -1;
		
		
		acceleration.y = acceleration.y/1000;
		*/
		firstChaotic = false;
	} else {
		if (position.x < 0)
			position.x = (double(rand())/RAND_MAX) * progmgr.getScreenX()+1000;
		if (position.y < 0)
			position.y = (double(rand())/RAND_MAX) * progmgr.getScreenY()+1000;
		position.x = position.x + velocity.x;
		position.y = position.y + velocity.y;
	}
}

