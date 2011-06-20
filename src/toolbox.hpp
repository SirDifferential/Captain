#ifndef __TOOLBOX_HPP_
#define __TOOLBOX_HPP_

#include <string>
#include <vector>

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
	std::vector<int> doubleVectorToIntVector(std::vector<double> in);
};

extern Toolbox tbox;

#endif
