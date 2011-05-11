#ifndef __TOOLBOX_HPP_
#define __TOOLBOX_HPP_

class Toolbox
{
private:
public:
	Toolbox();
	~Toolbox();

	int giveRandomInt();
	int giveRandomInt(int max);
};

extern Toolbox toolbox;

#endif
