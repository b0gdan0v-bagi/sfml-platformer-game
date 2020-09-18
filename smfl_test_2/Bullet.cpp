#include "Bullet.h"

using namespace sf;

Bullet::Bullet(AnimationManager& A, String Name, TileMap& lvl, float X, float Y, bool DIR, String TYPE) :Entity(A, Name, X, Y)
{
	obj = lvl.getObjectsByName("solid");// find solid objects
	x = X;
	y = Y;
	dir = DIR;
	speed = 0.8;
	damage = 10;
	life = true;
	type = TYPE;
	option(Name, 0.8, 1, "move");
}

void Bullet::update(float time)
{
	if (dir) dx = -speed;
	else dx = +speed;

	x += dx * time;//x moving
	y += dy * time;//y moving

	if (x <= 0) x = 1;// check for mistakes for out of map
	if (y <= 0) y = 1;

	for (int i = 0; i < obj.size(); i++) {//walk through solid objects
		if (getRect().intersects(obj[i].rect)) health = 0;//if this object collided with a bullet,

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