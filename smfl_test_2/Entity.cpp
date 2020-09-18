#include "Entity.h"

using namespace sf;

Entity::Entity(AnimationManager& A, std::string Name, float X, float Y)
{
	anim = A;
	x = X;
	y = Y;
	//w = W;
	//h = H;
	name = Name;
	health = 100;
	dx = 0;
	dy = 0;
	life = true;
	direction = false;
}

void Entity::draw(RenderWindow& window)
{
	anim.draw(window, x, y + h);
}

void Entity::option(std::string NAME, float SPEED, int HEALTH, std::string FIRST_ANIM)
{
	name = NAME;
	if (FIRST_ANIM != "") anim.set(FIRST_ANIM);
	w = anim.getW();
	h = anim.getH();
	dx = SPEED;
	health = HEALTH;
}