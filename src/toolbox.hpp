#ifndef __TOOLBOX_HPP_
#define __TOOLBOX_HPP_

#include <string>

class Toolbox
{
private:
public:
	Toolbox();
	~Toolbox();
	
	int timesRandomized;
	
	int giveRandomInt();
	int giveRandomInt(int min, int max);
	
	std::string charToString(char c);
};

extern Toolbox toolbox;

#endif
