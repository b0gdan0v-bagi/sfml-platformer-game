#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"


class Bullet :public Entity
{
public:
	bool dir;// bullet dirrection
	Bullet(AnimationManager& A, String Name, TileMap& lvl, float X, float Y, bool DIR) :Entity(A, Name, X, Y)
	{
		obj = lvl.getObjectsByName("solid");// find solid objects
		x = X;
		y = Y;
		dir = DIR;
		speed = 0.8;
		damage = 10;
		life = true;
		option(Name, 0.8, 1, "move");
	}


	void update(float time)
	{
		
		if (dir) dx = -speed;
		else dx = +speed;

		x += dx * time;//x moving
		y += dy * time;//y moving

		if (x <= 0) x = 1;// check for mistakes for out of map
		if (y <= 0) y = 1;

		for (int i = 0; i < obj.size(); i++) {//проход по объектам solid
			if (getRect().intersects(obj[i].rect)) //если этот объект столкнулся с пулей,
			{

				health = 0;
			}
		}
		if (health <= 0) 
		{
			damage = 0;
			anim.set("explode");
			speed = 0;
			if (anim.isPlaying() == false) life = false;
		}
		anim.tick(time);
	}
};

#endif  BULLET_H
