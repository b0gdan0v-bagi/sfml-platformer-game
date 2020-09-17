#pragma once
#include <SFML/Graphics.hpp>
#include "game.h"
#include "GlobalData.h"


int main()
{
    //RenderWindow window(VideoMode(800, 600), "privet");
    GlobalData data;
    int numberLevel = data.numberLevel;
    //gameRunning(window,numberLevel);
    gameRunning(numberLevel);
    //if (numberLevel > 2)     return 0;
    return 0;
}

