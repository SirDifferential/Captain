#include "timedFunctions.hpp"
#include "programManager.hpp"
#include "renderer.hpp"
#include "objectManager.hpp"

TimedFunctions triggers;

// For now, this test variable is resetted here. Ignore.
TimedFunctions::TimedFunctions()
{
	changed = false;
}

TimedFunctions::~TimedFunctions()
{
}

// Ask if there are any triggers that should be executed
void TimedFunctions::poll()
{
	if (progmgr.getTime() > 2 && progmgr.getTime() < 3 && !changed)
	{
		objectmgr.changeMainBackground("stars1024x1024.png");
		changed = true;
	}
}

