#ifndef __OBJLOADER_HPP_
#define __OBJLOADER_HPP_

#include <vector>

class ObjLoader
{
private:
public:
	ObjLoader();
	~ObjLoader();
	std::vector<std::vector<double> > readObjectFile(std::string path);
};

extern ObjLoader objectLoader;

#endif
