#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"

using namespace sf;

class Engine
{
private:

    RenderWindow m_Window;

    Sprite m_SpriteVodka;
    Texture m_TextureVodka;
    // Declaring the sprite and texture for the background
    Sprite m_BackgroundSprite;
    Texture m_BackgroundTexture;
    Vector2u TextureSize;  //Added to store texture size.
    Vector2u WindowSize;   //Added to store window size.

    // creation of volodya
    Player p_Player;
    Map m_Map;

    void input();
    void update(float dtAsSeconds);
    void draw();

public:


    // engine constructor
    Engine();

    // start call all private functions
    void start();

};