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

void Player::control() 
{
	if (Keyboard::isKeyPressed) {
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			state = left; speed = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			state = right; speed = 0.1;
		}

		if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround)) {
			state = jump; dy = -0.6; onGround = false;
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			state = down;
		}
	}
}

void Player::checkCollisionWithMap(float Dx, float Dy)
{

	for (int i = 0; i < obj.size(); i++)//ïðîõîäèìñÿ ïî îáúåêòàì
		if (getRect().intersects(obj[i].rect))//ïðîâåðÿåì ïåðåñå÷åíèå èãðîêà ñ îáúåêòîì
		{
			if (obj[i].name == "solid")//åñëè âñòðåòèëè ïðåïÿòñòâèå
			{
				if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx > 0) { x = obj[i].rect.left - w; }
				if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
			}
		}
}

void Player::update(float time)
{
	control();
	switch (state)
	{
	case right:dx = speed; break;
	case left:dx = -speed; break;
	case up: break;
	case down: dx = 0; break;
	case stay: break;
	}
	x += dx * time;
	checkCollisionWithMap(dx, 0);
	y += dy * time;
	checkCollisionWithMap(0, dy);
	sprite.setPosition(x + w / 2, y + h / 2);
	if (health <= 0) { life = false; }
	if (!isMove) { speed = 0; }
	//setPlayerCoordinateForView(x, y);
	if (life) { setPlayerCoordinateForView(x, y); }
	dy = dy + 0.0015 * time;
}
}