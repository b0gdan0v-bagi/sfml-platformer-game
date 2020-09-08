#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"


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

#endif  BULLET_H
