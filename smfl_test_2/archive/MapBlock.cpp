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
    m_rect = FloatRect(x, y, 32, 32);
    m_Sprite.setTextureRect(IntRect(0, 432, 32, 32));
}

void MapBlock::update(float elapsedTime)
{

    // move sprite
    m_Sprite.setPosition(m_rect.left, m_rect.top);

}