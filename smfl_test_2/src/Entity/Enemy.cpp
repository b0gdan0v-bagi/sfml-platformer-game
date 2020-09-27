#include "Enemy.h"

using namespace sf;

Enemy::Enemy(AnimationManager& A, String Name, TileMap& lvl, float X, float Y) :Entity(A, Name, X, Y) {
	m_obj = lvl.getObjectsByName("solid");
	option(Name, 0.1, 10, "move");
	m_anim.set("move");
	m_d.x = 0.1;
	if ((m_name == "EasyEnemy") || (m_name == "Skelleton"));
	{
		m_type = "enemy";
	}
}

void Enemy::checkCollisionWithMap(float Dx, float Dy)
{
	for (int i = 0; i < m_obj.size(); i++) // walk through solid objects
		if (getRect().intersects(m_obj[i].rect))//if this object collided with a enemy
		{
			if (m_obj[i].name == "solid") {
				if (Dy > 0) { m_rect.top = m_obj[i].rect.top - m_rect.height;  m_d.y = 0; m_onGround = true; }
				if (Dy < 0) { m_rect.top = m_obj[i].rect.top + m_obj[i].rect.height;   m_d.y = 0; }
				if (Dx > 0) { m_rect.left = m_obj[i].rect.left - m_rect.width;  m_d.x = -0.1; m_anim.flip(true); }
				if (Dx < 0) { m_rect.left = m_obj[i].rect.left + m_obj[i].rect.width; m_d.x = 0.1; m_anim.flip(false);}
			}
		}
}

void Enemy::update(float time)
{
	m_rect.left += m_d.x * time;
	checkCollisionWithMap(m_d.x, 0);
	m_rect.top += m_d.y * time;
	checkCollisionWithMap(0, m_d.y);
	if (m_health <= 0) { m_life = false; }
	m_d.y = m_d.y + 0.0015 * time;
	m_anim.tick(time);
}