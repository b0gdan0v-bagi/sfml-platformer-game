#include "Entity.h"

using namespace sf;

Entity::Entity(AnimationManager& A, std::string Name, float X, float Y)
{
	m_anim = A;
	m_rect.left = X;
	m_rect.top = Y;
	m_name = Name;
	m_health = 100;
	m_d.x = 0;
	m_d.y = 0;
	m_life = true;
	m_direction = false;
}

void Entity::draw(RenderWindow& window)
{
	m_anim.draw(window, m_rect.left, m_rect.top + m_rect.height);
}

void Entity::option(std::string NAME, float SPEED, int HEALTH, std::string FIRST_ANIM)
{
	m_name = NAME;
	if (FIRST_ANIM != "") m_anim.set(FIRST_ANIM);
	m_rect.width = m_anim.getW();
	m_rect.height = m_anim.getH();
	m_d.x = SPEED;
	m_health = HEALTH;
}