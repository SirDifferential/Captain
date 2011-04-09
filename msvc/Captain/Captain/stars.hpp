#ifndef _STARS_HPP_
#define _STARS_HPP_

#include <vector>
#include "vector3.hpp"

class Stars
{
public:
	Stars();
	~Stars();

	float opacity;
	void render();

private:
	class Star
	{
	public:
		Vector3 position;
		Vector3 color;
		int size;
		void render();
		Star(Stars *stars);
	private:
		Stars* stars;
	};

	std::vector<Star> stars;
};

#endif
