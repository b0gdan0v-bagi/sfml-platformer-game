#include "GlobalData.h"

using namespace sf;

GlobalData::GlobalData()
{
    config.open("config.cfg");
    if (!config.is_open())
    {
        std::cout << "Cannot open config.cfg\nUsing standart variables!\n";
        resolution.x = 1280;
        resolution.y = 720;
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
    config.close();

    numberLevel = 1;
    version = "ver 0.2";
    email = "bagizara@gmail.com";
    name = "Platformer";
}