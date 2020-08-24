#include "Engine.h"

using namespace sf;

void Engine::update(float dtAsSeconds)
{
    p_Player.update(dtAsSeconds);
    m_Map.update(dtAsSeconds);
}