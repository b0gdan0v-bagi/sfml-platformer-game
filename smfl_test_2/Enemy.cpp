#include "Enemy.h"

using namespace sf;

Enemy::Enemy(AnimationManager& A, String Name, TileMap& lvl, float X, float Y) :Entity(A, Name, X, Y) {
	obj = lvl.getObjectsByName("solid");
	option(Name, 0.1, 10, "move");
	anim.set("move");
	dx = 0.1;
	if ((name == "EasyEnemy") || (name == "Skelleton"));
	{
		type = "enemy";
	}
}

void Enemy::checkCollisionWithMap(float Dx, float Dy)
{
	for (int i = 0; i < obj.size(); i++) // walk through solid objects
		if (getRect().intersects(obj[i].rect))//if this object collided with a enemy
		{
			if (obj[i].name == "solid") {
				if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx > 0) { x = obj[i].rect.left - w;  dx = -0.1; anim.flip(true); }
				if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; anim.flip(false);}
			}
		}
}

void Enemy::update(float time)
{
	x += dx * time;
	checkCollisionWithMap(dx, 0);
	y += dy * time;
	checkCollisionWithMap(0, dy);
	if (health <= 0) { life = false; }
	dy = dy + 0.0015 * time;
	anim.tick(time);
}