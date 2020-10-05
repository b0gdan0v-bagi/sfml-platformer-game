#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"


class Enemy :public Entity
{
private:
	bool m_onGround;
	float m_shootTimer = { false };
	bool m_shooter = { false };


public:


	Enemy(AnimationManager& A, String Name, TileMap& lvl, float X, float Y);

	void checkCollisionWithMap(float Dx, float Dy);

	void update(float time);
};

#endif ENEMY_H
