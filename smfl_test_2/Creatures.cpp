#include "creatures.h"

Creatures::Creatures(Image& image, String Name, float X, float Y, int W, int H)
{
    x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
    speed = 0; health = 100; dx = 0; dy = 0;
    life = true; onGround = false; isMove = false;
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setOrigin(w / 2, h / 2);
}

FloatRect Creatures::getRect()
{//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
    return FloatRect(x, y, w, h);//эта ф-ция нужна для проверки столкновений 
}