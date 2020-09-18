#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"


class Enemy :public Entity
{
public:
	bool onGround;

	Enemy(AnimationManager& A, String Name, TileMap& lvl, float X, float Y);

	void checkCollisionWithMap(float Dx, float Dy);

	void update(float time);
};

#endif ENEMY_H
