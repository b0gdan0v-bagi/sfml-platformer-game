#ifndef CREATURES_H
#define CREATURES_H
#include <SFML/Graphics.hpp>
#include "animation.h"
#include "level.h"
#include <iostream>


using namespace sf;

class Entity {
public:
	AnimationManager anim;
	std::vector<Object> obj;//âåêòîð îáúåêòîâ êàðòû
	float dx, dy, x, y, w, h, timer;
	int health;
	bool life, direction;
	//Texture texture;
	//Sprite sprite;
	std::string name;

	//Entity(Image& image, String Name, float X, float Y, int W, int H)
	Entity(AnimationManager& A, std::string Name, float X, float Y, float W, float H)
	{
		anim = A;
		x = X;
		y = Y; 
		w = W; 
		h = H; 
		name = Name; 
		health = 100; 
		dx = 0;
		dy = 0;
		life = true;
		direction = false;
		//texture.loadFromImage(image);
		//sprite.setTexture(texture);
		//sprite.setOrigin(w / 2, h / 2);
	}

	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}
	virtual void update(float time) = 0;
	void draw(RenderWindow& window)
	{
		anim.draw(window, x, y + h);
	}
	void option(std::string NAME, float SPEED = 0, int HEALTH = 100, std::string FIRST_ANIM = "")
	{
		name = NAME;
		if (FIRST_ANIM != "") anim.set(FIRST_ANIM);
		w = anim.getW();
		h = anim.getH();
		dx = SPEED;
		health = HEALTH;
	}
};

class Player :public Entity 
{
public:
	enum { stay, walk, duck, jump, climb, swim } STATE;
	//enum { leftDir, rightDir} direction;
	std::map<std::string, bool> key;
	bool isShoot, win, onLadder, hit, canShoot;
	float shootTimer;

	Player(AnimationManager& A, String Name, TileMap& lev, float X, float Y, float W, float H) :Entity(A, Name, X, Y, W, H)
	{
		option(Name, 0, 100, "stay");
		obj = lev.getAllObjects();
		STATE = stay;
		win = false;
		hit = false;
		shootTimer = 0;
		canShoot = true;
	}

	void Keyboard()
	{
		if (key["L"])
		{
			direction = true;
			if (STATE != duck) dx = -0.15;
			if (STATE == stay) STATE = walk;
		}

		if (key["R"])
		{
			direction = false;
			if (STATE != duck) dx = 0.15;
			if (STATE == stay) STATE = walk;
		}

		if (key["Up"])
		{
			if (onLadder) STATE = climb;
			if (STATE == stay || STATE == walk) { dy = -0.37; STATE = jump; anim.play("stay"); }
			if (STATE == climb) dy = -0.05;
			if (STATE == climb) if (key["L"] || key["R"]) STATE = stay;
		}

		if (key["Down"])
		{
			if (STATE == stay || STATE == walk)
			{ 
				STATE = duck;
				dx = 0; 
			}
			if (STATE == climb) dy = 0.05;
		}

		if (key["Space"])
		{
			isShoot = true;
		}

		/////////////////////если клавиша отпущена///////////////////////////
		if (!(key["R"] || key["L"]))
		{
			dx = 0;
			if (STATE == walk) STATE = stay;
		}

		if (!(key["Up"] || key["Down"]))
		{
			if (STATE == climb) dy = 0;
		}

		if (!key["Down"])
		{
			if (STATE == duck) { STATE = stay; }
		}

		if (!key["Space"])
		{
			isShoot = false;
		}

		key["R"] = key["L"] = key["Up"] = key["Down"] = key["Space"] = false;
	}

	void Animation(float time)
	{
		if (STATE == stay) anim.set("stay");
		if (STATE == walk) anim.set("walk");
		if (STATE == jump) anim.set("jump");
		if (STATE == duck) anim.set("duck");
		if (STATE == climb) { anim.set("stay"); anim.pause(); if (dy != 0) anim.play(); }

		if (isShoot) {
			//anim.set("shoot");
			anim.set("stay");
			if (STATE == walk) anim.set("stay");
		}

		/*if (hit) {
			timer += time;
			if (timer > 1000) { hit = false; timer = 0; }
			anim.set("hit");
		}*/

		//if (direction) anim.flip();
		anim.flip(direction);

		anim.tick(time);
	}

	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = 0; i < obj.size(); i++)
			if (getRect().intersects(obj[i].rect))
			{
				if (obj[i].name == "solid")
				{
					if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; STATE = stay; }
					if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
					if (Dx > 0) { x = obj[i].rect.left - w; }
					if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
				}
				if (obj[i].name == "win")
				{
					win = true;
				}
				if (obj[i].name == "ladder") { onLadder = true; if (STATE == climb) x = obj[i].rect.left - 10; }
			}
	}

	void update(float time)
	{
		Keyboard();
		Animation(time);
		if (STATE == climb) if (!onLadder) STATE = stay;
		if (STATE != climb) dy += 0.0005 * time;
		if (!canShoot) // for delay in shooting
		{
			shootTimer += time;
			if (shootTimer > 600)
			{
				canShoot = true;
				shootTimer = 0;
			}
		}
		onLadder = false;
		x += dx * time;
		checkCollisionWithMap(dx, 0);
		y += dy * time;
		checkCollisionWithMap(0, dy);
		if (health <= 0) { life = false; }
	}
};

class Enemy :public Entity 
{
public:
	bool onGround;
	Enemy(AnimationManager& A, String Name, TileMap& lvl, float X, float Y, float W, float H) :Entity(A, Name, X, Y, W, H) {
		obj = lvl.getObjectsByName("solid");
		option(Name, 0.1, 1, "move");
		anim.set("move");
		if (name == "EasyEnemy") {
			//sprite.setTextureRect(IntRect(0, 0, w, h));
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
				if (Dx > 0) { x = obj[i].rect.left - w;  dx = -0.1; anim.flip(true); }
				if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; anim.flip(false);/* sprite.scale(-1, 1);*/ }
				}
			}
	}

	void update(float time)
	{
		if (name == "EasyEnemy") {
			//moveTimer += time;if (moveTimer>3000){ dx *= -1; moveTimer = 0; }
			x += dx * time;
			checkCollisionWithMap(dx, 0);
			y += dy * time;
			checkCollisionWithMap(0, dy);
			//sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) { life = false; }
			dy = dy + 0.0015 * time;
			anim.tick(time);
		}
	}
};

class Bullet :public Entity 
{
public:
	bool dir;// bullet dirrection
	float speed;
	Bullet(AnimationManager& A, String Name, TileMap& lvl, float X, float Y, float W, float H, bool DIR) :Entity(A, Name, X, Y, W, H) 
	{
		obj = lvl.getObjectsByName("solid");// find solid objects
		x = X;
		y = Y;
		dir = DIR;
		speed = 0.8;
		w = h = 16;
		life = true;
		option(Name, 0.8, 1, "move");
	}


	void update(float time)
	{
		anim.tick(time);
		if (dir) dx = -speed;
		else dx = +speed;

		x += dx * time;//x moving
		y += dy * time;//y moving

		if (x <= 0) x = 1;// check for mistakes for out of map
		if (y <= 0) y = 1;

		for (int i = 0; i < obj.size(); i++) {//проход по объектам solid
			if (getRect().intersects(obj[i].rect)) //если этот объект столкнулся с пулей,
			{
				life = false;// то пуля умирает
			}
		}
	}
};

#endif