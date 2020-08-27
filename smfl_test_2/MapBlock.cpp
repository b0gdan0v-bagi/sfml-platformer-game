#include "MapBlock.h"

MapBlock::MapBlock()
{
    passability = true;
}

// make sprite aviliable for draw()
Sprite MapBlock::getSprite()
{
    return m_Sprite;
}

Vector2f MapBlock::setPosition(int a, int b)
{
    return m_Position;
}

void MapBlock::set(Texture& image, int x, int y)
{
    m_Sprite.setTexture(image);
    m_Position.x = x;
    m_Position.y = y;
    m_rect = FloatRect(x, y, 40, 80);
    m_Sprite.setTextureRect(IntRect(0, 0, 40, 40));
}

void MapBlock::update(float elapsedTime)
{

    // move sprite
    m_Sprite.setPosition(m_rect.left, m_rect.top);

}