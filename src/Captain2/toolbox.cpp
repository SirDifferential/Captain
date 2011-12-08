#include "toolbox.hpp"
#include "manager.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

Toolbox tbox;

// Constructs our toolbox. Sets the random seed
Toolbox::Toolbox()
{
    fprintf(stderr, "A toolbox bought from the hardware store for 4.99 euros...\n");
    timesRandomized = 0;
    srand(time(0));
}

Toolbox::~Toolbox()
{
    fprintf(stderr, "A crappy toolbox being sold on ebay...\n");
}

// Returns a random integer
int Toolbox::giveRandomInt()
{
    timesRandomized++;
    return rand();
}

// Returns a random integer in range (min, max)
int Toolbox::giveRandomInt(int min, int max)
{
    return ((rand()%(max-min))+min);
}

// Checks if the specified file exists
bool Toolbox::fileExists(std::string path)
{
    bool result = false;
    std::ifstream fileChecker(path.c_str());
    if (fileChecker)
        result = true;
    else
        result = false;
    fileChecker.close();
    return result;
}

// Searches for a file upwards from the current dir
std::string Toolbox::searchFile(int range, std::string path)
{
    fprintf(stderr, "Searching %d directories upwards for %s\n", range, path.c_str());
    std::string beginPart = "";
    std::string entirePath = path;
    if (fileExists(entirePath))
        return entirePath;
    for (int i = 1; i < range; i++)
    {
        beginPart = appendToStringNTimes("../", i);
        entirePath = beginPart;
        entirePath.append(path);
        if (fileExists(entirePath))
            return entirePath;
    }
    return "";
}

SDL_Color Toolbox::getRandomColor()
{
    int min = 1;
    int max = 255;
    SDL_Color out;
    out.r = min + (double(rand())/RAND_MAX) * ((max-min) +1);
    out.g = min + (double(rand())/RAND_MAX) * ((max-min) +1);
    out.b = min + (double(rand())/RAND_MAX) * ((max-min) +1);
    return out;
}

SDL_Color Toolbox::getBWColor(SDL_Color in)
{
    SDL_Color out;
    
    // Meh, this should work well enough
    out.r = (in.r + in.b + in.g)/3;
    out.g = out.r;
    out.b = out.r;
    
    return out;
}

std::string Toolbox::appendToStringNTimes(std::string in, int numOfTimes)
{
    std::string out;
    for (int i = 0; i < numOfTimes; i++)
    {
        out.append(in);
    }
    return out;
}

// Converts a char into a string
std::string Toolbox::charToString(char c)
{
    std::stringstream stream;
    std::string out;
    stream << c;
    stream >> out;
    
    return out;
}

std::string Toolbox::intToString(int i)
{
    std::stringstream stream;
    std::string out;
    stream << i;
    stream >> out;

    return out;
}

// Converts std::vector<double> into std::vector<int>
// Used by the objLoader
std::vector<int> Toolbox::doubleVectorToIntVector(std::vector<double> in)
{
    std::vector<int> output;
    for (int i = 0; i < in.size(); i++)
    {
        output.push_back(int(in.at(i)));
    }
    return output;
}

// Returns the resolution of x*y in a string format
std::string Toolbox::resolutionToString(int sizeX, int sizeY)
{
    std::string output;
    std::stringstream container;
    container << sizeX;
    container << "x";
    container << sizeY;
    output = container.str();
    fprintf(stderr, "resolution is: %s\n", output.c_str());
    return output;
}

std::string Toolbox::stripString(std::string source, int quantity, std::string mode)
{
    std::string output;
    if (mode.compare("fromEnd") == 0)
    {
        for (int i = 0; i < source.length()-quantity; i++)
        {
            output.append(charToString(source.at(i)));
        }
    }
    else if (mode.compare("fromBegin") == 0)
    {
        for (int i = source.length()-quantity; i < source.length(); i++)
        {
            output.append(charToString(source.at(i)));
        }
    }
    else
    {
        fprintf(stderr, "Wrong string stripping mode given, assuming fromEnd\n");
        for (int i = 0; i < source.length() -quantity; i++)
        {
            output.append(charToString(source.at(i)));
        }
    }
    return output;
}

int Toolbox::boolToInt(bool b)
{
    if (b != 0)
        return true;
    else
        return false;
}


// Reverses a string. For example: banana becomes ananab
std::string Toolbox::reverseString(std::string toReverse)
{
    std::string out = "";
    for (int i = toReverse.length()-1; i >= 0; i--)
    {
        out.append(charToString(toReverse[i]));
    }
    fprintf(stderr, "Reversed a string: \n");
    fprintf(stderr, "%s\n", toReverse.c_str());
    fprintf(stderr, "%s\n", out.c_str());
    return out;
}
