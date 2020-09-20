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
    animationManagerList["player"].create("duck", imageList["player"], 0, 161, 40, 80, 1, 0);
    animationManagerList["player"].create("die", imageList["player"], 0, 81, 40, 80, 3, 0.01, 40);
    animationManagerList["player"].setLoop("die");
    animationManagerList["easyEnemy"].create("move", imageList["easyEnemy"], 0, 0, 32, 32, 1, 0.005);
    animationManagerList["skelleton"].loadFromXML("images/skelleton.xml", imageList["skelletonEnemy"]);
    animationManagerList["bullet"].create("move", imageList["bullet"], 7, 10, 8, 8, 1, 0);
    animationManagerList["bullet"].create("explode", imageList["bullet"], 27, 7, 18, 18, 4, 0.01, 29, false);
    return true;
}