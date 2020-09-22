#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>


using namespace sf;

class GlobalData
{
 private:
    std::ifstream config;
    std::string line, var1, var2;
    bool correctResolution = false; //check standart resolutions! dont want to have parser
public:
	int numberLevel;
    Vector2f resolution;
    std::string version, email, name;

    GlobalData();

};



#endif GLOBAL_DATA_H