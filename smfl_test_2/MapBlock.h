#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;

class MapBlock
{

private:


    Sprite m_Sprite;
    Texture m_Texture;
    //FloatRect m_rect;

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

public:

    MapBlock();

    Sprite getSprite();
    Vector2f setPosition(int j, int i);
    Vector2f m_Position;
    FloatRect m_rect;
    IntRect m_texture_rect;
    bool passability;


    // This function will be called every frame
    void set(Texture& image, int x, int y);
    void update(float elapsedTime);

}; 
