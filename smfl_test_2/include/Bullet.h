#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet :public Entity
{
private:
	bool m_horisontal;
	Vector2f m_speedVec;
public:

	Bullet(AnimationManager& A, String Name, TileMap& lvl, float X, float Y, bool DIR, String TYPE = "player1");
	Bullet(AnimationManager& A, String Name, TileMap& lvl, float X, float Y, float angle, String TYPE = "player1");
	void update(float time);
};

#endif  BULLET_H
