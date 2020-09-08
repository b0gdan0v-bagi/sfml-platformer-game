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
	float dx, dy, x, y, w, h, timer;
	int health;
	bool life, direction;
	//Texture texture;
	//Sprite sprite;
	std::string name;
	String type;

	Entity(AnimationManager& A, std::string Name, float X, float Y, float W, float H)
	{
		anim = A;
		x = X;
		y = Y;
		w = W;
		h = H;
		name = Name;
		health = 100;
		dx = 0;
		dy = 0;
		life = true;
		direction = false;
	}

	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}
	virtual void update(float time) = 0;
	void draw(RenderWindow& window)
	{
		anim.draw(window, x, y + h);
	}
	void option(std::string NAME, float SPEED = 0, int HEALTH = 100, std::string FIRST_ANIM = "")
	{
		name = NAME;
		if (FIRST_ANIM != "") anim.set(FIRST_ANIM);
		w = anim.getW();
		h = anim.getH();
		dx = SPEED;
		health = HEALTH;
	}
};

#endif ENTITY_H
