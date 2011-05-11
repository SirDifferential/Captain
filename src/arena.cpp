#include "arena.hpp"
#include "ProgramManager.hpp"
#include "toolbox.hpp"

typedef boost::shared_ptr<Planet> PlanetPtr;
typedef boost::shared_ptr<Sun> SunPtr;

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
	numberOfPlanets = toolbox.giveRandomInt(1, 15);
	numberOfSuns = toolbox.giveRandomInt(1, 3);
	std::cout << "There will be " << numberOfPlanets << " planets" << std::endl;
	std::cout << "There will be " << numberOfSuns << " suns" << std::endl;
	
	for (int i = 0; i < numberOfPlanets; i++)
	{
		int mass = toolbox.giveRandomInt(1000, 10000);
		int temperature = toolbox.giveRandomInt(0, 1000);
		int posX = toolbox.giveRandomInt(0, 1000);
		int posY = toolbox.giveRandomInt(0, 1000);
		PlanetPtr tempPtr(new Planet(mass, temperature, posX, posY));
		planetVector.push_back(tempPtr);
	}
	
	for (int i = 0; i < numberOfSuns; i++)
	{
		int mass = toolbox.giveRandomInt(10000, 100000);
		int temperature = toolbox.giveRandomInt(5000, 90000);
		int posX = toolbox.giveRandomInt(0, 10);
		int posY = toolbox.giveRandomInt(0, 10);
		SunPtr tempPtr(new Sun(mass, temperature, posX, posY));
		sunVector.push_back(tempPtr);
	}
}

void Arena::renderStars()
{
	starsPtr->render();
}
