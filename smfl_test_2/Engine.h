#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "MapC.h"
#include "MapBlock.h"

#include <vector>

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
    View view;
    // creation of volodya
    Player p_Player;
    MapC m_Map;
    MapBlock block[12][40];
  //  MapBlock blockTEST;
   
    void input();
    void update(float dtAsSeconds);
    void draw();
    void blocks();
    void setPlayerCoordinateForView(float x, float y);

public:


    // engine constructor
    Engine();

    // start call all private functions
    void start();

};