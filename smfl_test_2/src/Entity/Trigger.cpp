#include "Trigger.h"

using namespace sf;

Trigger::Trigger(AnimationManager& A, String Name, TileMap& lvl, float X, float Y, String TYPE) :Entity(A, Name, X, Y)
{
	m_rect.left = X;
	m_rect.height = Y;
	m_speed = 0.f;
	m_damage = 0.f;
	m_life = true;
	m_type = TYPE;
	m_name = Name;
	m_anim.set("stay");
	m_rect.width = m_anim.getW();
	m_rect.height = m_anim.getH();
	m_health = 1;
}

void Trigger::update(float time)
{
	if (m_health <= 0) m_life = false;
	m_anim.tick(time);
}