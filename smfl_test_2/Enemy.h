#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"


class Enemy :public Entity
{
public:
	bool onGround;
	//String type;

	Enemy(AnimationManager& A, String Name, TileMap& lvl, float X, float Y, float W, float H) :Entity(A, Name, X, Y, W, H) {
		obj = lvl.getObjectsByName("solid");
		option(Name, 0.1, 1, "move");
		anim.set("move");
		dx = 0.1;
		if ((name == "EasyEnemy") || (name == "Skelleton"));
		{
			type = "enemy";
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = 0; i < obj.size(); i++)//проходимся по объектам
			if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
			{
				if (obj[i].name == "solid") {//если встретили препятствие (объект с именем solid)
					if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
					if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
					if (Dx > 0) { x = obj[i].rect.left - w;  dx = -0.1; anim.flip(true); }
					if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; anim.flip(false);/* sprite.scale(-1, 1);*/ }
				}
			}
	}

	void update(float time)
	{
		//if (name == "EasyEnemy") {
			//moveTimer += time;if (moveTimer>3000){ dx *= -1; moveTimer = 0; }
		x += dx * time;
		checkCollisionWithMap(dx, 0);
		y += dy * time;
		checkCollisionWithMap(0, dy);
		//sprite.setPosition(x + w / 2, y + h / 2);
		if (health <= 0) { life = false; }
		dy = dy + 0.0015 * time;
		anim.tick(time);
		//}
	}
};

#endif ENEMY_H
