#include "engine.h"

using namespace sf;

bool Engine::loadImages()
{
    std::vector<std::string> imageName = { "bullet","player","easyEnemy", "skelletonEnemy" };
    for (std::vector<std::string>::iterator IMAGE = imageName.begin(); IMAGE != imageName.end(); ++IMAGE)
    {
        if (!imageList[*IMAGE].loadFromFile("images/" + *IMAGE + ".png"))
        {
            std::cout << "Cannot load " + *IMAGE + " image!";
            return false;
        }
    }

    imageList["skelletonEnemy"].createMaskFromColor(Color(255, 255, 255));
    imageList["easyEnemy"].createMaskFromColor(Color(0, 0, 0));
    imageList["player"].createMaskFromColor(Color(255, 255, 255));
    return true;
}
bool Engine::loadAnimations()
{
    animationManagerList["player"].create("walk", imageList["player"], 0, 0, 40, 80, 3, 0.01, 40);
    animationManagerList["player"].create("stay", imageList["player"], 0, 0, 40, 80, 1, 0);
    animationManagerList["player"].create("jump", imageList["player"], 0, 241, 40, 80, 1, 0);
    //animationManagerList["player"].create("duck", imageList["player"], 0, 161, 40, 80, 1, 0);
    animationManagerList["player"].create("duck", imageList["player"], 0, 0, 40, 40, 1, 0);
    animationManagerList["player"].create("die", imageList["player"], 0, 81, 40, 80, 3, 0.01, 40);
    animationManagerList["player"].setLoop("die");
    animationManagerList["easyEnemy"].create("move", imageList["easyEnemy"], 0, 0, 32, 32, 1, 0.005);
    animationManagerList["skelleton"].loadFromXML("images/skelleton.xml", imageList["skelletonEnemy"]);
    animationManagerList["bullet"].create("move", imageList["bullet"], 7, 10, 8, 8, 1, 0);
    animationManagerList["bullet"].create("explode", imageList["bullet"], 27, 7, 18, 18, 4, 0.01, 29, false);
    return true;
}

void Engine::gameRunning()

{
    window.setView(view);
    if (!levelUpper)
    {
        if (!menu.mainMenu(window, numberLevel)) return;
    }
    
    if (numberLevel == 3) pvp = true;
    else pvp = false;
    viewChanges(); // take view ports if screen splited or not
    entities.clear();
    players.clear();
    playerBars.clear();
    lvl.clear();
    inGameKeyInputs = true;
    returnToMainMenu = false;
    if (levelUpper) levelUpper = false;
    if (startGame())
    {
        
        gameRunning();
    }
}

void Engine::loadLevel()
{
    lvl.push_back(new TileMap);
    switch (numberLevel)
    {
    case 1:  lvl[0]->load("map1.tmx"); break;
    case 2:  lvl[0]->load("map1.tmx"); break;
    case 3:  lvl[0]->load("map_test2.tmx"); break;
    default:
        break;
    }
    Object player = lvl[0]->getObject("player");
    Object player2 = lvl[0]->getObject("player2");

    std::vector<Object> easyEnemy = lvl[0]->getObjectsByName("easyEnemy");
    std::vector<Object> skelleton = lvl[0]->getObjectsByName("skelleton");

    for (int i = 0; i < easyEnemy.size(); i++)
    {
        entities.push_back(new Enemy(animationManagerList["easyEnemy"],
            "EasyEnemy", *lvl[0], easyEnemy[i].rect.left, easyEnemy[i].rect.top));
    }
    for (int i = 0; i < skelleton.size(); i++)
    {
        entities.push_back(new Enemy(animationManagerList["skelleton"],
            "Skelleton", *lvl[0], skelleton[i].rect.left, skelleton[i].rect.top));
    }

    players.push_back(new Player(animationManagerList["player"], "Player1", *lvl[0], player.rect.left, player.rect.top));
    players.push_back(new Player(animationManagerList["player"], "Player2", *lvl[0], player2.rect.left, player2.rect.top));

    playerBars.push_back(new statBar(font, 1, true));
    playerBars.push_back(new statBar(font, 2));
    std::cout << "\n=========================\n";
    std::cout << "Level number : " << numberLevel << " is succsessfully loaded\n" << "pvp set : " << pvp << "\n";
    std::cout << "=========================\n";
}

void Engine::readConfig()
{
    std::ifstream config;
    std::string line, var1, var2;
    bool correctResolution = false; //check standart resolutions! dont want to have parser
    config.open("config.cfg");
    if (!config.is_open())
    {
        std::cout << "Cannot open config.cfg\nUsing standart variables!\n";
        resolution.x = 1280;
        resolution.y = 720;
        std::ofstream configWrite("config.cfg");
        if (configWrite.is_open())
        {
            configWrite << "resolution " << resolution.x << "x" << resolution.y;
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
        if ((var1 == "resolution"))
        {
            correctResolution = false;
            if (var2 == "1280x720") {
                resolution.x = 1280; resolution.y = 720;  correctResolution = true;
            }
            if (var2 == "1920x1080") {
                resolution.x = 1920; resolution.y = 1080;  correctResolution = true;
            }
            if (var2 == "3440x1440") {
                resolution.x = 3440; resolution.y = 1440;  correctResolution = true;
            }
            if (var2 == "1280x1024") {
                resolution.x = 1280; resolution.y = 1024;  correctResolution = true;
            }
            if (!correctResolution) {
                resolution.x = 1280;
                resolution.y = 720;
                std::cout << "Cannot find correct resolution\n";
            }
            std::cout << "Resolution set to " << resolution.x << "x" << resolution.y << "\n";
        }
    }
    std::cout << "Config readed!\n";
    config.close();
}

