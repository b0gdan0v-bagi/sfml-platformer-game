#include "MapC.h"

MapC::MapC()
{

    m_Sprite.setTextureRect(IntRect(m_rect));
 
}

// make sprite aviliable for draw()
Sprite MapC::getSprite()
{
    return m_Sprite;
}

Vector2f MapC::setPosition(int a, int b)
{
    return m_Position;
}


void MapC::update(float elapsedTime)
{

    // move sprite
    m_Sprite.setPosition(m_Position);

}
