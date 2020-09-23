#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>


using namespace sf;

struct GlobalData
{

	int numberLevel, numberLevelMax;
    Vector2f resolution;
    std::string version, email, name;

    void loadGlobalData();

};

#endif GLOBAL_DATA_H