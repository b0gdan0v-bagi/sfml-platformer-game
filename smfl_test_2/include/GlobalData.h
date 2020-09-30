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
    View viewInterface; // special view for menu
    int numberLevel;
    int const numberLevelMax = 3;
    int playersPVE;
    int const maxPlayersPVE = 2; // here is number of total supported players
    Vector2f resolution;
    std::string version, email, name;
    bool showFps;
    bool isChanged = { false };
    int fpsBarId;
    int const defaultHP = 20;
    int const defaultAMMO = 20;
    std::vector<int> playersHP = { defaultHP, defaultHP };
    std::vector<int> playersAMMO = { defaultAMMO, defaultAMMO };

    void loadGlobalData();
    void readConfig();
    void writeConfig();
    void setViewInterface();
};

#endif GLOBAL_DATA_H