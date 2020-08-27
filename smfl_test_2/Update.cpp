#include "Engine.h"

using namespace sf;

void Engine::update(float dtAsSeconds)
{
    p_Player.update(dtAsSeconds);
    m_Map.update(dtAsSeconds);
    for (int i = 0; i < m_Map.H; i++)
        for (int j = 0; j < m_Map.W; j++)
        {
            block[i][j].update(dtAsSeconds);
        }
}