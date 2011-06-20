<<<<<<< HEAD
#include "arena.hpp"
#include "programManager.hpp"
#include "toolbox.hpp"

typedef boost::shared_ptr<Planet> PlanetPtr;
typedef boost::shared_ptr<Sun> SunPtr;
typedef boost::shared_ptr<Object3D> Object3DPtr;

// Generate a new arena. This involves some randomness such as the amount
// of suns and planets
Arena::Arena()
{
	std::cout << "=====" << std::endl;
	std::cout << "New arena is being created" << std::endl;
	std::cout << "=====" << std::endl;
	generateNewArena();
}

// People don't comment their destructors enough, so here's a comment:
// This is the destructor, which is sligthly worrying. I mean, we are
// destructing an entire arena, an abstract plane of reality containing
// numerours planets and suns, possibly trillions of lives. All of them
// die in a flash of arithmetic without us ever hearing their screams.
// Makes you wonder.
Arena::~Arena()
{
}

void Arena::generateNewArena()
{
	// Generate a random static star background
	boost::shared_ptr<Stars> tempPtr(new Stars(false));
	starsPtr = tempPtr;
	
	// Add some planets and stars
	numberOfPlanets = tbox.giveRandomInt(1, 15);
	numberOfSuns = tbox.giveRandomInt(1, 10);
	std::cout << "There will be " << numberOfPlanets << " planets" << std::endl;
	std::cout << "There will be " << numberOfSuns << " suns" << std::endl;
	
	for (int i = 0; i < numberOfPlanets; i++)
	{
		int mass = tbox.giveRandomInt(1000, 10000);
		int temperature = tbox.giveRandomInt(0, 1000);
		int radius = tbox.giveRandomInt(100,5000);
		int posX = tbox.giveRandomInt(0, 1000);
		int posY = tbox.giveRandomInt(0, 1000);
		PlanetPtr tempPtr(new Planet(mass, temperature, radius, posX, posY));
		planetVector.push_back(tempPtr);
	}
	
	for (int i = 0; i < numberOfSuns; i++)
	{
		int mass = tbox.giveRandomInt(10000, 100000);
		int temperature = tbox.giveRandomInt(5000, 90000);
		int radius = tbox.giveRandomInt(10000, 100000);
		int posX = tbox.giveRandomInt(0, 10);
		int posY = tbox.giveRandomInt(0, 10);
		SunPtr tempPtr(new Sun(mass, temperature, radius, posX, posY));
		sunVector.push_back(tempPtr);
	}
	
	/*
	// Add some cubes for testing objects
	for (int i = 0; i < 10; i++)
	{
		Object3DPtr tempPtr(new Object3D("cube.obj"));
		objectVector.push_back(tempPtr);
	}
	*/
}

void Arena::render()
{
	renderStars();
	renderSuns();
	renderPlanets();
	renderObjects();
}

void Arena::renderStars()
{
	starsPtr->render();		// Background stars
}

void Arena::renderSuns()
{
	for (std::vector<SunPtr>::iterator iter = sunVector.begin(); iter != sunVector.end(); iter++)
	{
		(*iter)->render();
	}
}

void Arena::renderPlanets()
{
	for (std::vector<PlanetPtr>::iterator iter = planetVector.begin(); iter != planetVector.end(); iter++)
	{
		(*iter)->render();
	}
}

void Arena::renderObjects()
{
	for (std::vector<Object3DPtr>::iterator iter = objectVector.begin(); iter != objectVector.end(); iter++)
	{
		(*iter)->render();
	}
}

void Arena::update()
{
}

=======
#include "arena.hpp"
#include "programManager.hpp"
#include "toolbox.hpp"

typedef boost::shared_ptr<Planet> PlanetPtr;
typedef boost::shared_ptr<Sun> SunPtr;
typedef boost::shared_ptr<Object3D> Object3DPtr;

Arena::Arena()
{
	std::cout << "=====" << std::endl;
	std::cout << "New arena is being created" << std::endl;
	std::cout << "=====" << std::endl;
	generateNewArena();
}

Arena::~Arena()
{
}

void Arena::generateNewArena()
{
	// Generate a random static star background
	boost::shared_ptr<Stars> tempPtr(new Stars(false));
	starsPtr = tempPtr;
	
	// Add some planets and stars
	numberOfPlanets = tbox.giveRandomInt(1, 15);
	numberOfSuns = tbox.giveRandomInt(1, 10);
	std::cout << "There will be " << numberOfPlanets << " planets" << std::endl;
	std::cout << "There will be " << numberOfSuns << " suns" << std::endl;
	
	for (int i = 0; i < numberOfPlanets; i++)
	{
		int mass = tbox.giveRandomInt(1000, 10000);
		int temperature = tbox.giveRandomInt(0, 1000);
		int radius = tbox.giveRandomInt(100,5000);
		int posX = tbox.giveRandomInt(0, 1000);
		int posY = tbox.giveRandomInt(0, 1000);
		PlanetPtr tempPtr(new Planet(mass, temperature, radius, posX, posY));
		planetVector.push_back(tempPtr);
	}
	
	for (int i = 0; i < numberOfSuns; i++)
	{
		int mass = tbox.giveRandomInt(10000, 100000);
		int temperature = tbox.giveRandomInt(5000, 90000);
		int radius = tbox.giveRandomInt(10000, 100000);
		int posX = tbox.giveRandomInt(0, 10);
		int posY = tbox.giveRandomInt(0, 10);
		SunPtr tempPtr(new Sun(mass, temperature, radius, posX, posY));
		sunVector.push_back(tempPtr);
	}
	
	/*
	// Add some cubes for testing objects
	for (int i = 0; i < 10; i++)
	{
		Object3DPtr tempPtr(new Object3D("cube.obj"));
		objectVector.push_back(tempPtr);
	}
	*/
}

void Arena::render()
{
	renderStars();
	renderSuns();
	renderPlanets();
	renderObjects();
}

void Arena::renderStars()
{
	starsPtr->render();		// Background stars
}

void Arena::renderSuns()
{
	for (std::vector<SunPtr>::iterator iter = sunVector.begin(); iter != sunVector.end(); iter++)
	{
		(*iter)->render();
	}
}

void Arena::renderPlanets()
{
	for (std::vector<PlanetPtr>::iterator iter = planetVector.begin(); iter != planetVector.end(); iter++)
	{
		(*iter)->render();
	}
}

void Arena::renderObjects()
{
	for (std::vector<Object3DPtr>::iterator iter = objectVector.begin(); iter != objectVector.end(); iter++)
	{
		(*iter)->render();
	}
}
>>>>>>> a3564f92bac35322eed9894d4a7b261f56e74e3d
