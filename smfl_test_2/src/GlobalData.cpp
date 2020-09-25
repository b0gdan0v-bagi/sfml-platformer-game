#include "GlobalData.h"

using namespace sf;


void GlobalData::loadGlobalData()
{
    resolution.x = 1280;
    resolution.y = 720;
    numberLevel = 1;
    version = "ver 0.2";
    email = "bagizara@gmail.com";
    name = "Platformer";
    showFps = true;
    playersPVE = 1;
    fpsBarId = 1;
}
