#include "objLoader.hpp"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "toolbox.hpp"
#include <assert.h>

//#define DEBUG

ObjLoader objectLoader;

ObjLoader::ObjLoader()
{
}

ObjLoader::~ObjLoader()
{
}

// Open a .obj, load its contents into 3 arrays:
// 1. Vertices
// 2. Normals
// 3. Indices
// Returns a vector of vectors containing this data
std::vector<std::vector<double> > ObjLoader::readObjectFile(std::string path)
{
	int const bufferSize(1024);
	char lineBuffer[bufferSize];
	std::string line = "";
	int lineNumber = 0;
	int i = 0;
	std::fstream dataReader(path.c_str());
	std::string decimalNumberString = "";
	std::string integerNumberString = "";
	int coordinatesAdded = 0;
	
	double x, y, z = 0.0;
	int a, b, c = 0;
	
	std::vector<double> vertexData;			// Read vertexes here
	std::vector<double> normalData;			// Read normals here
	std::vector<double> indiceData;			// Read indices here
	std::vector<std::vector<double> > out;	// Return in this container
	
	if (!dataReader)
		std::cout << "Error opening model file: " << path.c_str() << std::endl;

	while (!dataReader.eof())
	{
		#ifdef DEBUG
		std::cout << "Linebreak" << std::endl;
		#endif
		dataReader.getline(lineBuffer, bufferSize);
		line = lineBuffer;
		
		if (line[0] == 'v' && line[1] == ' ')			// Vertex
		{
			coordinatesAdded = 0;
			decimalNumberString = "";
			// Start reading from the first number. Skip the leading v and whitespace
			for (int i = 2; coordinatesAdded < 3; i++)
			{
				if (line[i] == NULL)
					break;
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
				decimalNumberString.append(tbox.charToString(line[i]));
				
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
				if (line[i] == NULL)
					break;
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
				decimalNumberString.append(tbox.charToString(line[i]));
				
				if (coordinatesAdded > 3 && i > 40)
				{
					std::cout << "Something broke reading a 3D object. Consult your 3D model exporter" << std::endl;
					break;
				}
			}
			normalData.push_back(x);
			normalData.push_back(y);
			normalData.push_back(z);
		} else if (line[0] == 'f' && line[1] == ' ')	// Index
		{
			/*
			The syntax for indices is as follows:
			
			f 14//14474 4483//14474 7448//14474
			
			Where the first value is the vertex index and the following is probably a texture index.
			There is one value missing, and thus there are two "/" in sequence
			*/
			
			coordinatesAdded = 0;
			integerNumberString = "";
			bool valueAdded = false;
			a = 0;
			b = 0;
			c = 0;
			// Start reading from the first number. Skip the leading v and whitespace
			for (int i = 2; coordinatesAdded < 3; i++)
			{
				if (line[i] == NULL)
					break;
				// If we are at a new coordinate
				if (line[i] == ' ' || (coordinatesAdded == 2 && valueAdded == true) )
				{
					// Convert the string into an int
					if (coordinatesAdded == 0)
					{
						a = atoi(integerNumberString.c_str());
						#ifdef DEBUG
						std::cout << "a: " << a << std::endl;
						#endif
					}
					else if (coordinatesAdded == 1)
					{
						b = atoi(integerNumberString.c_str());
						#ifdef DEBUG
						std::cout << "b: " << b << std::endl;
						#endif
					}
					else if (coordinatesAdded == 2)
					{
						c = atoi(integerNumberString.c_str());
						#ifdef DEBUG
						std::cout << "c: " << c << std::endl;
						#endif
					}
					
					coordinatesAdded++;
					integerNumberString = "";
					valueAdded = false;
				}
				
				if (line[i] == '/')
				{
					valueAdded = true;
					#ifdef DEBUG
					std::cout << "Hit /" << std::endl;
					#endif
				}
				// Add the number or decimal dot to the string to be converted
				if (valueAdded == false)
				{
					#ifdef DEBUG
					std::cout << "reading an integer into a string: " << line[i] << std::endl;
					#endif
					integerNumberString.append(tbox.charToString(line[i]));
				}
				
				if (coordinatesAdded > 3 && i > 40)
				{
					std::cout << "Something broke reading a 3D object. Consult your 3D model exporter" << std::endl;
					break;
				}
			}
			
			assert(a);
			assert(b);
			assert(c);
			
			#ifdef DEBUG
			std::cout << "Pushing indices to vector: " << a << ", " << b << ", " << c << std::endl;
			#endif
			
			indiceData.push_back(a);
			indiceData.push_back(b);
			indiceData.push_back(c);
		} else {
			// Non-interesting data
		}
	}
	
	out.push_back(vertexData);
	out.push_back(normalData);
	out.push_back(indiceData);
	dataReader.close();
	
	return out;
}
