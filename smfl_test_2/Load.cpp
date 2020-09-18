#include "engine.h"

using namespace sf;

bool Engine::loadImages()
{
    if (!imageList["bullet"].loadFromFile("images/bullet.png"))
    {
        std::cout << "Cannot load bullet image!";
        return false;
    }
    imageList["hero"].loadFromFile("images/volodya.png");

    imageList["hero"].createMaskFromColor(Color(255, 255, 255));
    imageList["easyEnemy"].loadFromFile("images/kvak.png");
    imageList["easyEnemy"].createMaskFromColor(Color(0, 0, 0));
    imageList["skeletonEnemy"].loadFromFile("images/SkeletonWalk.png");
    imageList["skeletonEnemy"].createMaskFromColor(Color(255, 255, 255));
    return true;
}
bool Engine::loadAnimations()
{
    animationManagerList["player"].create("walk", imageList["hero"], 0, 0, 40, 80, 3, 0.01, 40);
    animationManagerList["player"].create("stay", imageList["hero"], 0, 0, 40, 80, 1, 0);
    animationManagerList["player"].create("jump", imageList["hero"], 0, 241, 40, 80, 1, 0);
    animationManagerList["player"].create("duck", imageList["hero"], 0, 161, 40, 80, 1, 0);
    animationManagerList["player"].create("die", imageList["hero"], 0, 81, 40, 80, 3, 0.01, 40, false);
    animationManagerList["easyEnemy"].create("move", imageList["easyEnemy"], 0, 0, 32, 32, 1, 0.005);
    animationManagerList["skelleton"].loadFromXML("images/skelleton.xml", imageList["skeletonEnemy"]);
    animationManagerList["bullet"].create("move", imageList["bullet"], 7, 10, 8, 8, 1, 0);
    animationManagerList["bullet"].create("explode", imageList["bullet"], 27, 7, 18, 18, 4, 0.01, 29, false);
    return true;
}