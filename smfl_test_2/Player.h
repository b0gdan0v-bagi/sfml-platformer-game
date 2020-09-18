#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player :public Entity
{
public:
	enum { stay, walk, duck, jump, climb, swim } STATE;
	std::map<std::string, bool> key;
	bool isShoot, win, onLadder, hit, canShoot;
	float shootTimer;
	int ammo;

	Player(AnimationManager& A, String Name, TileMap& lev, float X, float Y);
	void Keyboard();
	void Animation(float time);
	void checkCollisionWithMap(float Dx, float Dy);
	void update(float time);
};

#endif PLAYER_H