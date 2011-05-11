#ifndef __ARENA_HPP_
#define __ARENA_HPP_

#include "stars.hpp"
#include "planet.hpp"
#include "sun.hpp"
#include <boost/shared_ptr.hpp>

class Arena
{
private:
	int numberOfPlanets;
	int numberOfSuns;
	
	std::vector<boost::shared_ptr<Planet> > planetVector;
	std::vector<boost::shared_ptr<Sun> > sunVector;
	boost::shared_ptr<Stars> starsPtr;
	
public:
	Arena();
	Arena(std::string);
	~Arena();
	
	void generateNewArena();
	void renderStars();
};

#endif
