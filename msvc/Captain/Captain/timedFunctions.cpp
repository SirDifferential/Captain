#include "timedFunctions.hpp"
#include "programManager.hpp"
#include "renderer.hpp"

TimedFunctions triggers;

TimedFunctions::TimedFunctions()
{
	changed = false;
}

TimedFunctions::~TimedFunctions()
{
}

void TimedFunctions::poll()
{
	if (progmgr.getTime() > 2 && progmgr.getTime() < 3 && !changed)
	{
		renderer.changeBackground("stars1024x1024.png");
		changed = true;
	}
}