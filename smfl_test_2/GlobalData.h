#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <SFML/Graphics.hpp>

using namespace sf;

struct GlobalData
{
	int numberLevel = 1;
    Vector2f resolution;
    GlobalData()
    {
        Vector2f resolution;
        resolution.x = VideoMode::getDesktopMode().width;
        resolution.y = VideoMode::getDesktopMode().height;

        resolution.x = 1280;
        resolution.y = 720;
        //resolution.x = 1920;
        //resolution.y = 1080;
        //RenderWindow window(VideoMode(resolution.x, resolution.y), "privet");
    }
};



#endif GLOBAL_DATA_H