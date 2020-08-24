#include "Engine.h"

void Engine::draw()
{
    // Erasing the previous frame
    m_Window.clear(Color::White);
    m_Window.setMouseCursorVisible(false);

    // Rendering
    m_Window.draw(p_Player.getSprite());
    for (int i = 0; i < m_Map.H; i++)
        for (int j = 0; j < m_Map.W; j++)
        {
            if (m_Map.TileMap[i][j] == 'B')  m_SpriteVodka.setPosition(j * 40, i * 80);
            m_Window.draw(m_SpriteVodka); //test223ddddddddddz test ddddd
        }
    m_Window.display();
}