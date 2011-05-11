#ifndef _STARS_HPP_
#define _STARS_HPP_

#include <vector>
#include "vector3.hpp"

class Stars
{
public:
	Stars();
	Stars(bool speed);
	~Stars();

	float opacity;
	void render();
	void update();
	bool useSpeed;

private:
	class Star
	{
	public:
		Vector3 position;
		Vector3 velocity;
		Vector3 acceleration;
		Vector3 color;
		int size;
		void render();
		void update();
		Star(Stars *stars);
		bool firstChaotic;
	private:
		Stars* stars;
	};
	
	std::vector<Star> stars;
};

#endif
