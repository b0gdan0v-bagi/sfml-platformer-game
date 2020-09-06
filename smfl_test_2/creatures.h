#ifndef CREATURES_H
#define CREATURES_H
#include <SFML/Graphics.hpp>
#include "level.h"
#include "view.h"
#include <iostream>


using namespace sf;

class Entity {
public:
	std::vector<Object> obj;//âåêòîð îáúåêòîâ êàðòû
	float dx, dy, x, y, speed, moveTimer, currentFrame;
	int w, h, health;
	bool life, isMove, onGround;
	Texture texture;
	Sprite sprite;
	String name;
	Entity(Image& image, String Name, float X, float Y, int W, int H) {
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; health = 100; dx = 0; dy = 0;
		life = true; onGround = false; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}

	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}
	virtual void update(float time) = 0;
};

class Player :public Entity 
{
public:
	enum { left, right, up, down, jump, stay, RightTop } state;
	enum { leftDir, rightDir} direction;
	bool isShoot, win;
	int playerScore;

	Player(Image& image, String Name, TileMap& lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) 
	{
		health = 100;
		playerScore = 0; 
		state = stay;
		obj = lev.getAllObjects();
		currentFrame = 0;
		win = false;
		direction = rightDir;
		if (name == "Player1") {
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
	}

	void control() {
		if (!win)
		if (Keyboard::isKeyPressed) {
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				state = left;
				speed = 0.2; 
				direction = leftDir;
			}
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				state = right; 
				speed = 0.2; 
				direction = rightDir;
			}

			if ((Keyboard::isKeyPressed(Keyboard::W)) && (onGround)) {
				state = jump;
				dy = -0.8; 
				onGround = false;
			}


			if (Keyboard::isKeyPressed(Keyboard::S)) {
				state = down;
			}
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				isShoot = true;
			}
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = 0; i < obj.size(); i++)
			if (getRect().intersects(obj[i].rect))
			{
				if (obj[i].name == "solid")
				{
					if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
					if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
					if (Dx > 0) { x = obj[i].rect.left - w; }
					if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
				}
				if (obj[i].name == "win")
				{
					win = true;
				}
			}
	}

	void update(float time)
	{
		control();
		currentFrame += 0.005 * time;
		if (currentFrame > 3) currentFrame -= 3;
		switch (state)
		{
		case right: 
		{	

			//td::cout << currentFrame << " " << time << std::endl;
			if ((onGround) && (dx != 0))
			{ 
				sprite.setTextureRect(IntRect(w*int(currentFrame), 0, w, h)); 
			}
			dx = speed; 
			break; 
		}
		case left: 
		{
			dx = -speed;
			if ((onGround) && (dx != 0))
			{
				sprite.setTextureRect(IntRect(w * int(currentFrame), h, w, h));
			}
			break; 
		}
		case up: break;
		case down: 
		{
			dx = 0;
			if (direction == rightDir) { sprite.setTextureRect(IntRect(0, h * 2 + 1, w, h)); }
			else { sprite.setTextureRect(IntRect(41, h * 2 + 1, w, h)); }

			//sprite.setPosition(x, y + h / 2);
			break;
		}
		case jump:
		{
			if (direction == rightDir)
			{
				sprite.setTextureRect(IntRect(0, h * 3 + 1, w, h));
			}
			else
			{
				sprite.setTextureRect(IntRect(41, h * 3 + 1, w, h));
			}
			if (onGround)
			{
				if (direction = rightDir)
				{
					state = right;
					//sprite.setTextureRect(IntRect(0, 0, w, h));
				}
				else
				{
					state = left;
					//sprite.setTextureRect(IntRect(0, 0, w, h));
				}
			}
		}
		case stay: break;
		}
		x += dx * time;
		checkCollisionWithMap(dx, 0);
		y += dy * time;
		checkCollisionWithMap(0, dy);
		sprite.setPosition(x + w / 2, y + h / 2);
		if (health <= 0) { life = false; }
		if (!isMove) { speed = 0; }
		setPlayerCoordinateForView(x, y);
		//if (life) { setPlayerCoordinateForView(x, y); }
		dy = dy + 0.0015 * time;
	}
};

class Enemy :public Entity 
{
public:
	Enemy(Image& image, String Name, TileMap& lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
		obj = lvl.getObjectsByName("solid");//èíèöèàëèçèðóåì.ïîëó÷àåì íóæíûå îáúåêòû äëÿ âçàèìîäåéñòâèÿ âðàãà ñ êàðòîé
		if (name == "EasyEnemy") {
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dx = 0.1;
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = 0; i < obj.size(); i++)//ïðîõîäèìñÿ ïî îáúåêòàì
			if (getRect().intersects(obj[i].rect))//ïðîâåðÿåì ïåðåñå÷åíèå èãðîêà ñ îáúåêòîì
			{
				if (obj[i].name == "solid"){//åñëè âñòðåòèëè ïðåïÿòñòâèå (îáúåêò ñ èìåíåì solid)
				if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx > 0) { x = obj[i].rect.left - w;  dx = -0.1; sprite.scale(-1, 1); }
				if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; sprite.scale(-1, 1); }
				}
			}
	}

	void update(float time)
	{
		if (name == "EasyEnemy") {
			//moveTimer += time;if (moveTimer>3000){ dx *= -1; moveTimer = 0; }//ìåíÿåò íàïðàâëåíèå ïðèìåðíî êàæäûå 3 ñåê

			x += dx * time;
			checkCollisionWithMap(dx, 0);
			y += dy * time;
			checkCollisionWithMap(0, dy);
			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) { life = false; }
			dy = dy + 0.0015 * time;
		}
	}
};

class Bullet :public Entity {//класс пули
public:
	int direction;//направление пули

	Bullet(Image& image, String Name, TileMap& lvl, float X, float Y, int W, int H, int dir) :Entity(image, Name, X, Y, W, H) {//всё так же, только взяли в конце состояние игрока (int dir)
		obj = lvl.getObjectsByName("solid");//инициализируем .получаем нужные объекты для взаимодействия пули с картой
		x = X;
		y = Y;
		direction = dir;
		speed = 0.8;
		w = h = 16;
		life = true;
		//выше инициализация в конструкторе
	}


	void update(float time)
	{
		switch (direction)
		{
		case 0: dx = -speed; dy = 0;   break;//интовое значение state = left
		case 1: dx = speed; dy = 0;   break;//интовое значение state = right
		/*case 2: dx = 0; dy = -speed;   break;//интовое значение state = up
		case 3: dx = 0; dy = -speed;   break;//интовое значение не имеющее отношения к направлению, пока просто стрельнем вверх, нам сейчас это не важно
		case 4: dx = 0; dy = -speed;   break;//интовое значение не имеющее отношения к направлению, пока просто стрельнем вверх, нам сейчас это не важно
		case 5: dx = 0; dy = -speed;   break;//интовое значение не имеющее отношения к направлению, пока просто стрельнем вверх, нам сейчас это не важно*/
		}

		x += dx * time;//само движение пули по х
		y += dy * time;//по у

		if (x <= 0) x = 1;// задержка пули в левой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки
		if (y <= 0) y = 1;

		for (int i = 0; i < obj.size(); i++) {//проход по объектам solid
			if (getRect().intersects(obj[i].rect)) //если этот объект столкнулся с пулей,
			{
				life = false;// то пуля умирает
			}
		}

		sprite.setPosition(x + w / 2, y + h / 2);//задается позицию пуле
	}
};

#endif