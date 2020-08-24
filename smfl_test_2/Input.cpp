#include "Engine.h"

void Engine::input()
{
    // Escape Press
    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
        m_Window.close();
    }

    // Press moving keys
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        p_Player.moveLeft();
    }
    else
    {
        p_Player.stopLeft();
    }

    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        p_Player.moveRight();
    }
    else
    {
        p_Player.stopRight();
    }

    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        p_Player.moveTop();
    }
    else
    {
        p_Player.stopTop();
    }

    if (Keyboard::isKeyPressed(Keyboard::S))
    {
        p_Player.moveBot();
    }
    else
    {
        p_Player.stopBot();
    }

}