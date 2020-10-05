#include "Player.h"

using namespace sf;

Player::Player(AnimationManager& A, String Name, TileMap& lev, float X, float Y) :Entity(A, Name, X, Y)
{
	m_rectDuck.width = m_anim.getW("duck");
	m_rectDuck.height = m_anim.getH("duck");
	
	option(Name, 0, 20, "stay");
	m_obj = lev.getAllObjects();
	m_STATE = stay;
	win = false;
	m_hit = false;
	m_shootTimer = 0;
	canShoot = true;
	ammo = 20;
	m_doorKey = false;
	//std::cout << "duck size" << m_duckSize.x << " " << m_duckSize.y << "\nNormal size" << m_rect.width << " " << m_rect.height << "\n";
}

void Player::Keyboard()
{
	if (m_key["L"])
	{
		m_direction = true;
		if (m_STATE != duck) m_d.x = -0.25;
		if (m_STATE == stay) m_STATE = walk;
	}

	if (m_key["R"])
	{
		m_direction = false;
		if (m_STATE != duck) m_d.x = 0.25;
		if (m_STATE == stay) m_STATE = walk;
	}

	if (m_key["Up"])
	{
		if (m_onLadder) m_STATE = climb;
		if (m_STATE == stay || m_STATE == walk) { m_d.y = -0.37; m_STATE = jump; m_anim.play("stay"); }
		if (m_STATE == climb) m_d.y = -0.05;
		if (m_STATE == climb) if (m_key["L"] || m_key["R"]) m_STATE = stay;
	}

	if (m_key["Down"])
	{
		if (m_STATE == stay || m_STATE == walk)
		{
			m_STATE = duck;
			m_d.x = 0;
		}
		if (m_STATE == climb) m_d.y = 0.05;
	}

	if (m_key["Space"])
	{
		isShoot = true;
	}

	//if key unpressed
	if (!(m_key["R"] || m_key["L"]))
	{
		m_d.x = 0;
		if (m_STATE == walk) m_STATE = stay;
	}

	if (!(m_key["Up"] || m_key["Down"]))
	{
		if (m_STATE == climb) m_d.y = 0;
	}

	if (!m_key["Down"])
	{
		if (m_STATE == duck) { m_STATE = stay; }
	}

	if (!m_key["Space"])
	{
		isShoot = false;
	}

	m_key["R"] = m_key["L"] = m_key["Up"] = m_key["Down"] = m_key["Space"] = false;
}

void Player::Animation(float time)
{
	if (m_STATE == stay) m_anim.set("stay");
	if (m_STATE == walk) m_anim.set("walk");
	if (m_STATE == jump) m_anim.set("jump");
	if (m_STATE == duck) m_anim.set("duck");
	if (m_STATE == climb) 
	{
		m_anim.set("climb"); 
		m_anim.pause(); 
		if (m_d.y != 0) m_anim.play(); 
	}

	if (isShoot) {
		//m_anim.set("shoot");
		m_anim.set("stay");
		if (m_STATE == walk) m_anim.set("stay");
	}

	/*if (hit) {
		timer += time;
		if (timer > 1000) { hit = false; timer = 0; }
		m_anim.set("hit");
	}*/

	//if (direction) m_anim.flip();
	m_anim.flip(m_direction);
	if (m_health <= 0)
	{
		m_health = 0;
		m_anim.set("die");

		if (m_anim.isPlaying() == false)
		{
			m_life = false;
		}
	}

	m_anim.tick(time);
}

void Player::checkCollisionWithMap(float Dx, float Dy)
{
	for (int i = 0; i < m_obj.size(); i++)
		if (getRect().intersects(m_obj[i].rect))
		{
			if ((m_obj[i].name == "solid") || ((m_obj[i].name == "door") && (!m_doorKey)))
			{
				if (Dy > 0) { m_rect.top = m_obj[i].rect.top - m_rect.height;  m_d.y = 0; m_STATE = stay; }
				if (Dy < 0) { m_rect.top = m_obj[i].rect.top + m_obj[i].rect.height;   m_d.y = 0; }
				if (Dx > 0) { m_rect.left = m_obj[i].rect.left - m_rect.width; }
				if (Dx < 0) { m_rect.left = m_obj[i].rect.left + m_obj[i].rect.width; }
			}
			if (m_obj[i].name == "win")
			{ 
				win = true;
			}
			if (m_obj[i].name == "ladder") 
			{ 
				m_onLadder = true; 
				if (m_STATE == climb) m_rect.left = m_obj[i].rect.left - 10; 
			}
		}
} 

void Player::update(float time)
{
	ifDuck();
	if (m_health > 0) Keyboard();
	Animation(time);
	if (m_STATE == climb) if (!m_onLadder) m_STATE = stay;
	if (m_STATE != climb) m_d.y += 0.0005 * time;
	
	/*if (m_STATE != duck) m_StayPos = Vector2f(m_rect.left, m_rect.top);
	else 
	{ 
		m_rect.left = m_StayPos.x + m_duckDiff.x;
		m_rect.top = m_StayPos.y + m_duckDiff.y;
	}*/
	
	if (!canShoot) // for delay in shooting
	{
		m_shootTimer += time;
		if (m_shootTimer > 600)
		{
			canShoot = true;
			m_shootTimer = 0;
		}
	}
	m_onLadder = false;
	if (m_health > 0) m_rect.left += m_d.x * time;
	checkCollisionWithMap(m_d.x, 0);
	if (m_health > 0) m_rect.top += m_d.y * time;
	checkCollisionWithMap(0, m_d.y);
	m_rectDuck.left = m_rect.left;
	m_rectDuck.top = m_rectDuck.top + m_rect.height - m_rectDuck.height;
	ifDuck();
	
}

bool Player::ifDuck() 
{ 
	if (m_anim.get() == "duck") return true;
	else return false;
}
