#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player :public Entity
{
public:
	enum { stay, walk, duck, jump, climb, swim } STATE;
	//enum { leftDir, rightDir} direction;
	std::map<std::string, bool> key;
	bool isShoot, win, onLadder, hit, canShoot;
	float shootTimer;
	int ammo;

	Player(AnimationManager& A, String Name, TileMap& lev, float X, float Y) :Entity(A, Name, X, Y)
	{
		option(Name, 0, 100, "stay");
		obj = lev.getAllObjects();
		STATE = stay;
		win = false;
		hit = false;
		shootTimer = 0;
		canShoot = true;
		ammo = 20;
	}

	void Keyboard()
	{
		if (key["L"])
		{
			direction = true;
			if (STATE != duck) dx = -0.25;
			if (STATE == stay) STATE = walk;
		}

		if (key["R"])
		{
			direction = false;
			if (STATE != duck) dx = 0.25;
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

#endif PLAYER_H