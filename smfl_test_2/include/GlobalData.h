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
    View viewInterface; // special view for interface //maybe add std::map for all views (now we have special in menu.h)
    int numberLevel = { 1 };
    int const numberLevelMax = 3;
    int numberLevelAvailiable = { 1 };
    int playersPVE = { 1 };
    int const maxPlayersPVE = 2; // here is number of total supported players
    Vector2f resolution = { Vector2f(1280,720) };
    std::string const version = { "ver 0.3" }, email = { "bagizara@gmail.com" }, name = { "Platformer" };
    bool showFps = { true };
    bool isChanged = { false };
    int fpsBarId = { 1 };
    int const defaultHP = 20;
    int const defaultAMMO = 20;
    std::vector<int> playersHP = { defaultHP, defaultHP };
    std::vector<int> playersAMMO = { defaultAMMO, defaultAMMO };

    std::string const defaultName = { "Volodya" };
    std::vector<std::string> playersName = { defaultName ,defaultName };

    std::string const defaultModel = { "player" };
    std::vector<std::string> playersModel = { defaultModel ,defaultModel };

    float musicVolume = {30.f };
    float sndVolume = { 15.f };
    std::string musicVolumeString;
    std::string sndVolumeString;

    // player stat
    int numberOfShots = { 0 };
    int numberOfShotsSum = { 0 };
    int numberOfKilled = { 0 };
    int numberOfKilledSum = { 0 };
    int numberOfBottlesGained = { 0 };
    int numberOfBottlesGainedSum = { 0 };

    std::string nOfShotsStr, nOfKilledStr, nOfBotGainedStr;

    void setContersToString();
    void zeroPlayerStat(bool isGlobal = false);
    void calculateSumStat();
    void volumeToString();
    void readConfig();
    void writeConfig();
    void setViewInterface();
};

#endif GLOBAL_DATA_H