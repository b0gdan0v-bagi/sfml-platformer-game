#include "Bullet.h"

using namespace sf;

Bullet::Bullet(AnimationManager& A, String Name, TileMap& lvl, float X, float Y, bool DIR, String TYPE) :Entity(A, Name, X, Y)
{
	m_obj = lvl.getObjectsByName("solid");// find solid objects
	m_rect.left = X;
	m_rect.height = Y;
	m_direction = DIR;
	m_speed = 0.8;
	m_damage = 10;
	m_life = true;
	m_type = TYPE;
	option(Name, 0.8, 1, "move");
}

void Bullet::update(float time)
{
	if (m_direction) m_d.x = -m_speed;
	else m_d.x = +m_speed;

	m_rect.left += m_d.x * time;//x moving
	m_rect.height += m_d.y * time;//y moving

	if (m_rect.left <= 0) m_rect.left = 1;// check for mistakes for out of map
	if (m_rect.height <= 0) m_rect.height = 1;

	for (int i = 0; i < m_obj.size(); i++)
	{//walk through solid objects
		if (getRect().intersects(m_obj[i].rect)) m_health = 0;//if this object collided with a bullet
	}
	if (m_health <= 0)
	{
		m_damage = 0;
		m_anim.set("explode");
		m_speed = 0;
		if (m_anim.isPlaying() == false) m_life = false;
	}
	m_anim.tick(time);
}