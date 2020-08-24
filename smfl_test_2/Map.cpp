#include "Map.h"

Map::Map()
{

    m_Sprite.setTextureRect(IntRect(m_rect));
 
}

// make sprite aviliable for draw()
Sprite Map::getSprite()
{
    return m_Sprite;
}

Vector2f Map::setPosition(int a, int b)
{
    return m_Position;
}


void Map::update(float elapsedTime)
{

    // move sprite
    m_Sprite.setPosition(m_Position);

}