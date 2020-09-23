#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet :public Entity
{
public:

	Bullet(AnimationManager& A, String Name, TileMap& lvl, float X, float Y, bool DIR, String TYPE = "player1");
	void update(float time);
};

#endif  BULLET_H
