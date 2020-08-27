#include "Engine.h"
#include <iostream>

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
            //if (m_Map.TileMap[i][j] == 'B')  m_SpriteVodka.setPosition(j * 40, i * 80);
            //m_Window.draw(m_SpriteVodka); //test223ddddddddddz test ddddd
            
            m_Window.draw(block[i][j].getSprite());
        }
    m_Window.display();
}

void Engine::blocks()
{
    for (int i = 0; i < m_Map.H; i++)
        for (int j = 0; j < m_Map.W; j++)
        {
            if (m_Map.TileMap[i][j] == 'B')
            {
                block[i][j].passability = false;
                block[i][j].set(m_TextureVodka, j * 40, i * 40);
            }
            else
            {
                block[i][j].set(m_TextureVodka, 1000, 1000);
            }
        }
}

void Engine::intersects()
{   

    /*for (int i = p_Player.p_rect.top / 40; i < (p_Player.p_rect.top + p_Player.p_rect.height) / 40; i++)
        for (int j = p_Player.p_rect.left / 40; j < (p_Player.p_rect.left + p_Player.p_rect.width) / 40; j++)*/
    for (int i = 0; i < m_Map.H; i++)
        for (int j = 0; j < m_Map.W; j++)
        {
           // std::cout << " i " << i << " j " << j << std::endl;
            if (!block[i][j].passability)
            {
                if (p_Player.getSprite().getGlobalBounds().intersects(block[i][j].getSprite().getGlobalBounds()))
                {
                    //p_Player.p_Velocity.x = 0;
                    //p_Player.p_Velocity.y = 0;
                    //std::cout << "hello" << std::endl;
                    //
                    std::cout << " i " << i << " j " << j << std::endl;
                    std::cout << "passability "  << block[i][j].passability << std::endl;
                    std::cout << "block[i][j].m_rect.left " << block[i][j].m_rect.left << std::endl;
                    std::cout << "p_Player.p_rect.left " << p_Player.p_rect.left << std::endl;

                    //if (p_Player.p_Velocity.x > 0) p_Player.p_rect.left = j * 40 - 40;
                    //std::cout << "p_Player.p_rect.width " << p_Player.p_rect.width << std::endl;
                    /*if ((p_Player.p_rect.left + 40 > block[i][j].m_rect.left) && (p_Player.p_rect.left + 20 < block[i][j].m_rect.left + 20))
                    {
                         p_Player.p_rect.left = j * 40 - 40;
                    }
                    if ((p_Player.p_rect.left < block[i][j].m_rect.left + 40) && (p_Player.p_rect.left + 20 > block[i][j].m_rect.left + 20)) 
                    {
                        p_Player.p_rect.left = j * 40 + 40; 
                    }
                    if ((p_Player.p_rect.top + 80 > block[i][j].m_rect.top) && (p_Player.p_rect.top + 40 < block[i][j].m_rect.left + 20))
                    {
                        p_Player.p_rect.top = i * 40 - 80;
                    }
                    if ((p_Player.p_rect.top < block[i][j].m_rect.top + 40) && (p_Player.p_rect.top + 40 > block[i][j].m_rect.left + 20))
                    {
                        p_Player.p_rect.top = i * 40 + 40;
                    }*/
                    if (p_Player.p_Direction.x > 0)
                    {
                        p_Player.p_rect.left = j * 40 - 40;
                    }
                    if (p_Player.p_Direction.x < 0)
                    {
                        p_Player.p_rect.left = j * 40 + 40;
                    }
                    if (p_Player.p_Direction.y > 0)
                    {
                        p_Player.p_rect.top = i * 40 - 80;
                        p_Player.onGround = true;
                        p_Player.p_Velocity.y = 0;
                    }
                    if (p_Player.p_Direction.y < 0)
                    {
                        p_Player.p_rect.top = i * 40 + 40;
                    }
                    //if (p_Player.p_rect.top + 80 > block[i][j].p_rect.top) p_Player.p_rect.top = i * 40 - 40;// block[i][j].p_rect.left;
                    ///if (p_Player.p_rect.top < block[i][j].p_rect.top + 80) p_Player.p_rect.top = i * 40;// block[i][j].p_rect.left;
                    
                }
            }
        }
    /*for (int i = p_Player.p_rect.top / 40; i < (p_Player.p_rect.top + p_Player.p_rect.height) / 40; i++)
        for (int j = p_Player.p_rect.left / 40; j < (p_Player.p_rect.left + p_Player.p_rect.width) / 40; j++)
        {
            if (!block[i][j].passability)
            {
                if ((p_Player.p_Velocity.x > 0) && (!block[i][j].passability)) p_Player.p_rect.left = j * 40 - p_Player.p_rect.width;
                if ((p_Player.p_Velocity.x < 0) && (!block[i][j].passability)) p_Player.p_rect.left = j * 40 + 40;
                if ((p_Player.p_Velocity.y > 0) && (!block[i][j].passability)) { p_Player.p_rect.top = i * 40 - p_Player.p_rect.height; p_Player.p_Velocity.y = 0;   p_Player.onGround = true; }
                if ((p_Player.p_Velocity.y < 0) && (!block[i][j].passability)) { p_Player.p_rect.top = i * 40 + 40;   p_Player.p_Velocity.y = 0; }

            }

        }*/
} 