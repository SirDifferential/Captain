#include "objLoader.hpp"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "toolbox.hpp"

ObjLoader objectLoader;

ObjLoader::ObjLoader()
{
}

ObjLoader::~ObjLoader()
{
}

std::vector<std::vector<double> > ObjLoader::readObjectFile(std::string path)
{
	int const bufferSize(1024);
	char lineBuffer[bufferSize];
	std::string line = "";
	int lineNumber = 0;
	int i = 0;
	std::fstream dataReader(path.c_str());
	std::string decimalNumberString = "";
	int coordinatesAdded = 0;
	
	double x, y, z = 0.0;
	
	std::vector<double> vertexData;			// Read vertexes here
	std::vector<double> indiceData;			// read indices here
	std::vector<double> normalData;			// Read normals here
	std::vector<std::vector<double> > out;	// Return in this container
	
	if (!dataReader)
		std::cout << "Error opening model file: " << path.c_str() << std::endl;

	while (!dataReader.eof())
	{
		dataReader.getline(lineBuffer, bufferSize);
		line = lineBuffer;
		
		
		if (line[0] == 'v' && line[1] == ' ')			// Vertex
		{
			coordinatesAdded = 0;
			decimalNumberString = "";
			// Start reading from the first number. Skip the leading v and whitespace
			for (int i = 2; coordinatesAdded < 3; i++)
			{
				// If we are at a new coordinate
				if (line[i] == ' ')
				{
					// Convert the string into a double
					if (coordinatesAdded == 0)
						x = atof(decimalNumberString.c_str());
					else if (coordinatesAdded == 1)
						y = atof(decimalNumberString.c_str());
					else if (coordinatesAdded == 2)
						z = atof(decimalNumberString.c_str());
					
					coordinatesAdded++;
					decimalNumberString = "";
				}
				
				// Add the number or decimal dot to the string to be converted
				decimalNumberString.append(toolbox.charToString(line[i]));
				
				if (coordinatesAdded > 3 && i > 40)
				{
					std::cout << "Something broke reading a 3D object. Consult your 3D model exporter" << std::endl;
					break;
				}
			}
			vertexData.push_back(x);
			vertexData.push_back(y);
			vertexData.push_back(z);
		} else if (line[0] == 'v' && line[1] == 'n')	// Vertex normal
		{
			coordinatesAdded = 0;
			decimalNumberString = "";
			// Start reading from the first number. Skip the leading v and whitespace
			for (int i = 3; coordinatesAdded < 3; i++)
			{
				// If we are at a new coordinate
				if (line[i] == ' ')
				{
					// Convert the string into a double
					if (coordinatesAdded == 0)
						x = atof(decimalNumberString.c_str());
					else if (coordinatesAdded == 1)
						y = atof(decimalNumberString.c_str());
					else if (coordinatesAdded == 2)
						z = atof(decimalNumberString.c_str());
					
					coordinatesAdded++;
					decimalNumberString = "";
				}
				
				// Add the number or decimal dot to the string to be converted
				decimalNumberString.append(toolbox.charToString(line[i]));
				
				if (coordinatesAdded > 3 && i > 40)
				{
					std::cout << "Something broke reading a 3D object. Consult your 3D model exporter" << std::endl;
					break;
				}
			}
			normalData.push_back(x);
			normalData.push_back(y);
			normalData.push_back(z);
		} else if (line[0] == 'f' && line[1] == ' ')	// Face
		{
			// Do nothing
		}
	}
	
	out.push_back(vertexData);
	out.push_back(normalData);
	out.push_back(indiceData);
	dataReader.close();
	
	return out;
}
