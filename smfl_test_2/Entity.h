#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "animation.h"
#include "level.h"
#include <iostream>


using namespace sf;

class Entity {
public:
	AnimationManager anim;
	std::vector<Object> obj;
	float dx, dy, x, y, w, h, speed;
	float damage, timer;
	int health;
	bool life, direction, onDie;
	std::string name;
	String type;

	Entity(AnimationManager& A, std::string Name, float X, float Y);

	FloatRect getRect() { return FloatRect(x, y, w, h); }
	virtual void update(float time) = 0;
	void draw(RenderWindow& window);
	void option(std::string NAME, float SPEED = 0, int HEALTH = 100, std::string FIRST_ANIM = "");
};

#endif 
