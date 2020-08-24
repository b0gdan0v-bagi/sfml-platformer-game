#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Map
{

private:

    
    Sprite m_Sprite;
    Texture m_TextureVodka;
    FloatRect m_rect;



public:

    Map();

    Sprite getSprite();
    Vector2f setPosition(int j, int i);
    Vector2f m_Position;

    const int H = 12;
    const int W = 40;


    String TileMap[12] = {

    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                B     B",
    "B                                B     B",
    "B                                B     B",
    "B                                B     B",
    "B         0000                BBBB     B",
    "B                                B     B",
    "BBB                              B     B",
    "B              BB                BB    B",
    "B              BB                      B",
    "B    B         BB         BB           B",
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",

    };
    
    // This function will be called every frame
    void update(float elapsedTime);

};
