#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "animation.h"
#include "level.h"
#include <iostream>


using namespace sf;

class Entity {
private:


protected:
	Vector2f m_d;
	FloatRect m_rect;
	float m_speed;
	std::vector<Object> m_obj;
	float m_damage, m_timer;
	int m_health;
	bool m_life, m_direction, m_onDie;
	AnimationManager m_anim;
	std::string m_name;
	std::string m_type;
public:

	Entity(AnimationManager& A, std::string Name, float X, float Y);

	FloatRect getRect() { return m_rect; }
	Vector2f getPos() { return Vector2f(m_rect.left,m_rect.top); }
	std::string getType() { return m_type; }
	std::string getName() { return m_name; }
	bool getLife() { return m_life; }
	float getDamage() { return m_damage; }
	Vector2f getSpeed() { return m_d; }
	void setSpeedX(float dX) { m_d.x = dX; }
	void setSpeedY(float dY) { m_d.y = dY; }
	void setDamage(float damage) { m_damage = damage; }
	void setDamage() { m_damage = 0.f; }
	int getHealth() { return m_health; }
	void setHealth(int health) { m_health = health; }
	void takeDamage(int damage) { m_health -= damage; }
	void takeHP(int hp) { m_health += hp; }
	void kill() { m_life = false; }

	bool getDir() { return m_direction; }



	virtual void update(float time) = 0;
	void draw(RenderWindow& window);
	void option(std::string NAME, float SPEED = 0, int HEALTH = 100, std::string FIRST_ANIM = "");
};

#endif 
