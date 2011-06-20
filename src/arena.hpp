#ifndef __ARENA_HPP_
#define __ARENA_HPP_

#include "stars.hpp"
#include "planet.hpp"
#include "sun.hpp"
#include "object3d.hpp"
#include <boost/shared_ptr.hpp>

class Arena
{
private:
	int numberOfPlanets;
	int numberOfSuns;
	
	std::vector<boost::shared_ptr<Planet> > planetVector;
	std::vector<boost::shared_ptr<Sun> > sunVector;
	boost::shared_ptr<Stars> starsPtr;
	std::vector<boost::shared_ptr<Object3D> > objectVector;
	
public:
	Arena();
	Arena(std::string);
	~Arena();
	
	void update();
	void generateNewArena();
	void render();
	void renderStars();
	void renderSuns();
	void renderPlanets();
	void renderObjects();
};

#endif
