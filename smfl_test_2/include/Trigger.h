#ifndef TRIGGER_H
#define TRIGGER_H

#include "Entity.h"

class Trigger :public Entity
{
public:

	Trigger(AnimationManager& A, String Name, TileMap& lvl, float X, float Y, String TYPE = "normal");
	void update(float time);
};

#endif  TRIGGER_H
