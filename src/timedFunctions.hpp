#ifndef __TIMEDFUNCTIONS_HPP_
#define __TIMEDFUNCTIONS_HPP_

class TimedFunctions
{
private:
	bool changed;
public:
	TimedFunctions();
	~TimedFunctions();

	void poll();
};

extern TimedFunctions triggers;

#endif
