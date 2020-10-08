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
	Vector2f m_duckDiff, m_StayPos;
	bool m_doorKey;
	
public:
	bool isShoot, canShoot, win;
	int ammo;

	Player(AnimationManager& A, String Name, TileMap& lev, float X, float Y);
	void Keyboard();
	void Animation(float time);
	void checkCollisionWithMap(float Dx, float Dy);
	void update(float time);
	void setKey(std::string keyNAME, bool BOOL = true) { m_key[keyNAME] = BOOL; }
	bool ifDuck(); // for checking intersects with bullet and no conflicts with collisions
	void setDoorKey(bool DOOR_KEY) { m_doorKey = DOOR_KEY; }
	bool getDoorKey() { return m_doorKey; }
	Vector2f getDuckDiff() { return m_duckDiff; }

};

#endif PLAYER_H