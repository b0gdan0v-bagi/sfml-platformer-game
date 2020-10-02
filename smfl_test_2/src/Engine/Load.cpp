#include "engine.h"

using namespace sf;

bool Engine::loadImages()
{
    std::vector<std::string> imageName = { "bullet","player","easyEnemy", "skelletonEnemy", "vodka",
        "door", "key", "trigger", "char" };
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
    animationManagerList["char"].loadFromXML("resourses/images/char.xml", imageList["char"]);
    animationManagerList["char"].setLoop("die");

    return true;
}

void Engine::gameRunning()

{
    
    if (!levelChanger)
    {
        if (!menu.mainMenu(window, data)) return;
    }

    window.setView(data.viewInterface);

    if (data.isChanged)  data.isChanged = false;
    if (data.numberLevel / 100 != 0) pvp = true;
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
    // delete memory for global engine vectors
    for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) delete *it;
    entities.clear(); 
    for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); ++it) delete* it;
    players.clear();
    for (std::vector<statBar*>::iterator it = playerBars.begin(); it != playerBars.end(); ++it) delete* it;
    playerBars.clear();
    for (std::vector<TileMap*>::iterator it = lvl.begin(); it != lvl.end(); ++it) delete* it;
    lvl.clear(); 
    for (std::vector<Message*>::iterator it = messages.begin(); it != messages.end(); ++it) delete* it;
    messages.clear();
    gameSTATE = 0;
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
    numberLevelStream << data.numberLevel;
    // lvls for pvp have id > 100
    lvl[0]->load("resourses/maps/map" + numberLevelStream.str() + ".tmx");

    loadEnemyWave(0);
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
            load[i].GetPropertyString("text"))); //in text we have new messages!
    }


    int numberOfPlayersToAdd;
    if (pvp) numberOfPlayersToAdd = 2;
    else numberOfPlayersToAdd = data.playersPVE;
    for (int i = 1; i <= numberOfPlayersToAdd; ++i)
    {
        std::ostringstream playerN;
        playerN << i;
        Object player = lvl[0]->getObject("player" + playerN.str());
        players.push_back(new Player(animationManagerList[data.playersModel[i-1]], "Player" + playerN.str(), *lvl[0], player.rect.left, player.rect.top));
        std::cout << "player" + playerN.str() << " added!\n";
        playerBars.push_back(new statBar(font, pvp, i));
    }
    // size of vectors for reloads must be equal to number of added players!
    while (data.playersAMMO.size() < numberOfPlayersToAdd) data.playersAMMO.push_back(data.defaultAMMO);
    while (data.playersHP.size() < numberOfPlayersToAdd) data.playersHP.push_back(data.defaultHP);
    while (data.playersName.size() < numberOfPlayersToAdd) data.playersName.push_back(data.defaultName);

    for (int i = 0; i < players.size(); ++i)
    {
        players[i]->ammo = data.playersAMMO[i];
        players[i]->setHealth(data.playersHP[i]);
    }
    if (!pvp) task = "Go forward!";
    std::cout << "\n=========================\n";
    std::cout << "Level number : " << data.numberLevel << " is succsessfully loaded\n" << "pvp set : " << pvp << "\n";
    std::cout << "=========================\n";
}

void Engine::loadEnemyWave(int waveN)
{
    std::ostringstream waveNstream;
    waveNstream << waveN;
    std::vector<std::string> vObjEnemy;
    vObjEnemy = { "easyEnemy", "skelleton", };
    for (std::vector<std::string>::iterator itObj = vObjEnemy.begin(); itObj != vObjEnemy.end(); ++itObj)
    {
        std::vector<Object> load = lvl[0]->getObjectsByName(*itObj);
        if (waveN != 0) load = lvl[0]->getObjectsByName(*itObj + waveNstream.str());
        for (int i = 0; i < load.size(); i++)
        {
            entities.push_back(new Enemy(animationManagerList[*itObj],
                *itObj, *lvl[0], load[i].rect.left, load[i].rect.top));
        }
    }
    addNewWave = false;
}


