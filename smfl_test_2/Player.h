#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player :public Entity
{
private:
	enum { stay, walk, duck, jump, climb, swim } m_STATE;
	std::map<std::string, bool> m_key;
	bool m_onLadder, m_hit;
	float m_shootTimer;
	
public:
	bool isShoot, canShoot, win;
	int ammo;

	Player(AnimationManager& A, String Name, TileMap& lev, float X, float Y);
	void Keyboard();
	void Animation(float time);
	void checkCollisionWithMap(float Dx, float Dy);
	void update(float time);
	void setKey(std::string keyNAME, bool BOOL = true) { m_key[keyNAME] = BOOL; }
};

#endif PLAYER_H