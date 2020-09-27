#include "engine.h"

using namespace sf;

bool Engine::loadImages()
{
    std::vector<std::string> imageName = { "bullet","player","easyEnemy", "skelletonEnemy", "vodka",
        "door", "key", "trigger" };
    for (std::vector<std::string>::iterator IMAGE = imageName.begin(); IMAGE != imageName.end(); ++IMAGE)
    {
        if (!imageList[*IMAGE].loadFromFile("resourses/images/" + *IMAGE + ".png"))
        {
            std::cout << "Cannot load " + *IMAGE + " image!";
            return false;
        }
    }

    imageList["skelletonEnemy"].createMaskFromColor(Color(255, 255, 255));
    imageList["easyEnemy"].createMaskFromColor(Color(0, 0, 0));
    imageList["player"].createMaskFromColor(Color(255, 255, 255));
    imageList["vodka"].createMaskFromColor(Color(255, 255, 255));
    imageList["key"].createMaskFromColor(Color(255, 255, 255));
    imageList["trigger"].createMaskFromColor(Color(0, 0, 0));
    return true;
}
bool Engine::loadAnimations()
{
    animationManagerList["player"].create("walk", imageList["player"], 0, 0, 40, 80, 3, 0.01, 40);
    animationManagerList["player"].create("stay", imageList["player"], 0, 0, 40, 80, 1, 0);
    animationManagerList["player"].create("jump", imageList["player"], 0, 241, 40, 80, 1, 0);
    animationManagerList["player"].create("duck", imageList["player"], 0, 0, 40, 40, 1, 0);
    animationManagerList["player"].create("die", imageList["player"], 0, 81, 40, 80, 3, 0.01, 40);
    animationManagerList["player"].setLoop("die");
    animationManagerList["easyEnemy"].create("move", imageList["easyEnemy"], 0, 0, 32, 32, 1, 0.005);
    animationManagerList["skelleton"].loadFromXML("resourses/images/skelleton.xml", imageList["skelletonEnemy"]);
    animationManagerList["bullet"].create("move", imageList["bullet"], 7, 10, 8, 8, 1, 0);
    animationManagerList["bullet"].create("explode", imageList["bullet"], 27, 7, 18, 18, 4, 0.01, 29, false);
    animationManagerList["vodka"].create("stay", imageList["vodka"], 0, 0, 17, 37, 1, 0.005);
    animationManagerList["door"].create("stay", imageList["door"], 0, 0, 32, 64, 1, 0.005);
    animationManagerList["key"].create("stay", imageList["key"], 0, 0, 22, 13, 1, 0.005);
    animationManagerList["trigger"].create("stay", imageList["trigger"], 0, 0, 1, 400, 1, 0.005); //virtual

    return true;
}

void Engine::gameRunning()

{
    window.setView(view);
    if (!levelChanger)
    {
        if (!menu.mainMenu(window, numberLevel)) return;
    }
    
    if (numberLevel / 100 != 0) pvp = true;
    else pvp = false;
    viewChanges(); // take view ports if screen splited or not
    if (levelChanger) levelChanger = false; //level changer works once
    else // restore DATA to defaults
    {
        for (int i = 0; i < data.playersAMMO.size(); ++i) 
        {
            data.playersAMMO[i] = data.defaultAMMO;
            data.playersHP[i] = data.defaultHP;
        }
    }
    entities.clear(); // delete memory for global engine vectors
    players.clear();
    playerBars.clear();
    lvl.clear(); 
    messages.clear();
    inGameKeyInputs = true; //make sure that keybord for players is working
    returnToMainMenu = false; //break bool for main cycle
    
    if (startGame()) // main cycle of game 
    {
        gameRunning(); //loop game runs
    }
}

void Engine::loadLevel()
{
    lvl.push_back(new TileMap); 
    std::ostringstream numberLevelStream;
    numberLevelStream << numberLevel;
    // lvls for pvp have id > 100
    lvl[0]->load("resourses/maps/map" + numberLevelStream.str() + ".tmx");

    std::vector<std::string> vObjEnemy = { "easyEnemy", "skelleton",};
    for (std::vector<std::string>::iterator itObj = vObjEnemy.begin(); itObj != vObjEnemy.end(); ++itObj)
    {
        std::vector<Object> load = lvl[0]->getObjectsByName(*itObj);
        for (int i = 0; i < load.size(); i++)
        {
            entities.push_back(new Enemy(animationManagerList[*itObj],
                *itObj, *lvl[0], load[i].rect.left, load[i].rect.top));
            
        }
    }
    std::vector<std::string> vObjTrig = {"vodka", "door", "key"};
    for (std::vector<std::string>::iterator itObj = vObjTrig.begin(); itObj != vObjTrig.end(); ++itObj)
    {
        std::vector<Object> load = lvl[0]->getObjectsByName(*itObj);
        for (int i = 0; i < load.size(); i++)
        {
            entities.push_back(new Trigger(animationManagerList[*itObj],
                *itObj, *lvl[0], load[i].rect.left, load[i].rect.top));
        }
    }
    std::vector<Object> load = lvl[0]->getObjectsByName("trigger");
    for (int i = 0; i < load.size(); i++)
    {
        entities.push_back(new Trigger(animationManagerList["trigger"],
            "trigger", *lvl[0], load[i].rect.left, load[i].rect.top,
            load[i].GetPropertyString("text")));
    }


    int numberOfPlayersToAdd;
    if (pvp) numberOfPlayersToAdd = 2;
    else numberOfPlayersToAdd = data.playersPVE;
    for (int i = 1; i <= numberOfPlayersToAdd; ++i)
    {
        std::ostringstream playerN;
        playerN << i;
        Object player = lvl[0]->getObject("player" + playerN.str());
        players.push_back(new Player(animationManagerList["player"], "Player" + playerN.str(), *lvl[0], player.rect.left, player.rect.top));
        std::cout << "player" + playerN.str() << " added!\n";
        playerBars.push_back(new statBar(font, pvp, i));
        //data.showFps = false; // we want fps counter only for 1st
    }
    // size of vectors for reloads must be equal to number of added players!
    while (data.playersAMMO.size() < numberOfPlayersToAdd) data.playersAMMO.push_back(data.defaultAMMO);
    while (data.playersHP.size() < numberOfPlayersToAdd) data.playersHP.push_back(data.defaultHP);

    for (int i = 0; i < players.size(); ++i)
    {
        players[i]->ammo = data.playersAMMO[i];
        players[i]->setHealth(data.playersHP[i]);
    }

    std::cout << "\n=========================\n";
    std::cout << "Level number : " << numberLevel << " is succsessfully loaded\n" << "pvp set : " << pvp << "\n";
    std::cout << "=========================\n";
}

void Engine::readConfig()
{
    std::ifstream config;
    std::string line, var1, var2;
    std::vector<String> AvaliableResolutions = { "1280x720","1920x1080","3440x1440","1280x1024" };
    config.open("config.cfg");
    if (!config.is_open())
    {
        std::cout << "Cannot open config.cfg\nUsing standart variables!\n";
        resolution.x = 1280;
        resolution.y = 720;
        data.playersPVE = 1;
        data.showFps = true;
        data.fpsBarId = 1;
        std::ofstream configWrite("config.cfg");
        if (configWrite.is_open())
        {
            configWrite << "//Availiable resolutions = {1280x720,1920x1080,3440x1440,1280x1024}\n";
            configWrite << "resolution " << resolution.x << "x" << resolution.y << "\n";
            configWrite << "showFps " << data.showFps << "\n";
            configWrite << "PlayersPVE " << data.playersPVE << "\n";
            configWrite << "ShowFpsType " << data.fpsBarId << "\n";
            configWrite.close();
            std::cout << "Standart config created!\n";
        }
        else std::cout << "Unable to create config.cfg file\n";
        return;
    }
    while (std::getline(config, line))
    {
        std::istringstream iss(line);
        if (!(iss >> var1 >> var2)) { break; } // end
        std::cout << "Read config: " << var1 << " " << var2 << "\n";
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
                std::string resX = var2.substr(0,posX);
                std::string resY = var2.substr(posX+1);
                resolution.x = std::stoi(resX);
                resolution.y = std::stoi(resY);
                if ((resolution.x < 200) || (resolution.x > 3440)) resolution.x = 1280;
                if ((resolution.y < 200) || (resolution.x > 2160)) resolution.y = 720;
            }
            std::cout << "Resolution set to " << resolution.x << "x" << resolution.y << "\n";
        }
        if (var1 == "showFps")
        {
            if ((var2 == "1") || (var2 == "true")) {
                data.showFps = true;
            }
            else data.showFps = false;
            std::cout << "showFps set to " << data.showFps << "\n";
        }
        if (var1 == "PlayersPVE")
        {
            data.playersPVE = std::stoi(var2);
            if (data.playersPVE < 1) data.playersPVE = 1;
            if (data.playersPVE > data.maxPlayersPVE) data.playersPVE = data.maxPlayersPVE;
            std::cout << "Number of PVE players set to " << data.playersPVE << "\n";
        }
        if (var1 == "ShowFpsType")
        {
            data.fpsBarId = std::stoi(var2);
            if ((data.fpsBarId != 0) || (data.fpsBarId != 1)) data.fpsBarId == 0;
        }
    }
    std::cout << "Config readed!\n";
    config.close();
}

