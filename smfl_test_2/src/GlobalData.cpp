#include "GlobalData.h"

using namespace sf;

void GlobalData::zeroPlayerStat()
{
    numberOfShots = 0;
    numberOfShotsSum = 0;
    numberOfKilled = 0;
    numberOfKilledSum = 0;
    numberOfBottlesGained = 0;
    numberOfBottlesGainedSum = 0;
}

void GlobalData::calculateSumStat()
{
    numberOfShotsSum += numberOfShots;
    numberOfKilledSum += numberOfKilled;
    numberOfBottlesGainedSum += numberOfBottlesGained;
    numberOfShots = 0;
    numberOfKilled = 0;
    numberOfBottlesGained = 0;
}

void GlobalData::volumeToString()
{
    if (musicVolume == 0) musicVolumeString = "off";
    else  musicVolumeString = std::to_string((int)musicVolume);
    if (sndVolume == 0) sndVolumeString = "off";
    else sndVolumeString = std::to_string((int)sndVolume);
}

void GlobalData::readConfig()
{
    std::ifstream config;
    std::string line, var1, var2;
    std::vector<String> AvaliableResolutions = { "1280x720","1920x1080","3440x1440","1280x1024" };
    config.open("config.cfg");
    if (!config.is_open())
    {
        std::cout << "Cannot open config.cfg\nUsing standart variables!\n";
        writeConfig();
        return;
    }
    while (std::getline(config, line))
    {
        std::istringstream iss(line);
        if (!(iss >> var1 >> var2)) { break; } // end
        //std::cout << "Read config: " << var1 << " " << var2 << "\n";
        if ((var1 == "resolution"))
        {
            std::string findX = "x";
            std::size_t posX = var2.find(findX);
            if (posX == std::string::npos)
            {
                std::cout << "Incorrect resolution in config\n";
                resolution.x = 1280;
                resolution.y = 720;
            }
            else
            {
                std::string resX = var2.substr(0, posX);
                std::string resY = var2.substr(posX + 1);
                resolution.x = std::stoi(resX);
                resolution.y = std::stoi(resY);
                if ((resolution.x < 200) || (resolution.x > 3440)) resolution.x = 1280;
                if ((resolution.y < 200) || (resolution.y > 2160)) resolution.y = 720;
            }
            std::cout << "Resolution set to " << resolution.x << "x" << resolution.y << "\n";
        }
        if (var1 == "showFps")
        {
            if ((var2 == "1") || (var2 == "true")) {
                showFps = true;
            }
            else showFps = false;
            std::cout << "showFps set to " << showFps << "\n";
        }
        if (var1 == "PlayersPVE")
        {
            playersPVE = std::stoi(var2);
            if (playersPVE < 1) playersPVE = 1;
            if (playersPVE > maxPlayersPVE) playersPVE = maxPlayersPVE;
            std::cout << "Number of PVE players set to " << playersPVE << "\n";
        }
        if (var1 == "ShowFpsType")
        {
            fpsBarId = std::stoi(var2);
            if ((fpsBarId != 0) && (fpsBarId != 1)) fpsBarId == 0;
        }
        if (var1 == "PlayerName_1")
        {
            playersName[0] = var2;
        }
        if (var1 == "PlayerName_2")
        {
            playersName[1] = var2;
        }
        if (var1 == "PlayerModel_1")
        {
            playersModel[0] = var2;
        }
        if (var1 == "PlayerModel_2")
        {
            playersModel[1] = var2;
        }
        if (var1 == "music_volume")
        {
            musicVolume = std::stoi(var2);
            if ((musicVolume < 0) || (musicVolume > 100)) musicVolume = 30;
        }
        if (var1 == "snd_volume")
        {
            sndVolume = std::stoi(var2);
            if ((sndVolume < 0) || (sndVolume > 100)) sndVolume = 15;
        }
        if (var1 == "lvl_able")
        {
            numberLevelAvailiable = std::stoi(var2);
            
            if ((numberLevelAvailiable < 1) || (numberLevelAvailiable > numberLevelMax)) numberLevelAvailiable = 1;
            std::cout << numberLevelAvailiable << " numberLevelAvailiable\n";
        }
    }
    std::cout << "Config readed!\n";
    config.close();
}

void GlobalData::writeConfig()
{
    std::ofstream configWrite("config.cfg");
    if (configWrite.is_open())
    {
        configWrite << "//Availiable resolutions = {1280x720,1920x1080,3440x1440,1280x1024}\n";
        configWrite << "resolution " << resolution.x << "x" << resolution.y << "\n";
        configWrite << "showFps " << showFps << "\n";
        configWrite << "PlayersPVE " << playersPVE << "\n";
        configWrite << "ShowFpsType " << fpsBarId << "\n";
        for (int i = 0; i < playersName.size(); i++)
        {
            std::ostringstream p;
            p << i+1;
            configWrite << "PlayerName_" + p.str() << " " << playersName[i] << "\n";
        }
        configWrite << "// Availiable player models : char, player \n";
        for (int i = 0; i < playersModel.size(); i++)
        {
            std::ostringstream p;
            p << i + 1;
            configWrite << "PlayerModel_" + p.str() << " " << playersModel[i] << "\n";
        }
        configWrite << "music_volume " << musicVolume << "\n";
        configWrite << "snd_volume " << sndVolume << "\n";
        configWrite << "lvl_able " << numberLevelAvailiable << "\n";
        configWrite.close();
        std::cout << "Standart config created!\n";
    }
    else std::cout << "Unable to create config.cfg file\n";
}

void GlobalData::setViewInterface()
{
    viewInterface.setCenter(resolution.x / 2, resolution.y / 2);
    viewInterface.setSize(resolution);
}

