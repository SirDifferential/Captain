#ifndef __SUN_HPP_
#define __SUN_HPP_

#include "vector3.hpp"
#include "object3d.hpp"
#include <boost/shared_ptr.hpp>

class Sun
{
private:
	int mass;
	int temperature;
	int radius;
	Vector3 position;
	double angle;
	float angle2;
	Vector3 colour;
	boost::shared_ptr<Object3D> modelPointer;
public:
	Sun();
	Sun(int mass, int temperature, int radius, int posX, int posY);
	~Sun();
	
	void render();
};

#endif
