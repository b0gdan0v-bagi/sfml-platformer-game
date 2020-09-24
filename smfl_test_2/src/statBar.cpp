#include "statBar.h"

using namespace sf;

statBar::statBar(Font& font, bool PVP, int PLAYER_NUMBER)
{
	m_playerNo = PLAYER_NUMBER;
	m_playerText.setFont(font);
	m_pvp = PVP;
}


void statBar::update(std::string name, int hp, int ammo, float time)
{
	std::ostringstream playerHealthString;
	std::ostringstream playerAmmoString;

	playerHealthString << hp;
	playerAmmoString << ammo;
	m_playerText.setString(name + " HP : " + playerHealthString.str() + "\n" + name + " ammo : " + playerAmmoString.str());
}

void statBar::draw(RenderWindow& window)
{
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();
	m_playerText.setCharacterSize(size.y / 25);
	//m_playerText.setCharacterSize(20);
	m_playerText.setFillColor(Color::White);
	m_horisontalStrip = RectangleShape(Vector2f(size.x, size.y / 10));
	m_horisontalStrip.setFillColor(Color::Black);
	m_playerText.setPosition(center.x - size.x / 2, center.y + size.y / 2 - size.y / 10 + 1);
	m_horisontalStrip.setPosition(center.x - size.x / 2, center.y + size.y / 2 - size.y / 10);
	if (m_pvp)
	{
		if (m_playerNo == 1)
		{
			m_verticalStrip = RectangleShape(Vector2f(10, size.y));
			m_verticalStrip.setPosition(center.x + size.x / 2 - 10, center.y - size.y / 2);
			m_verticalStrip.setFillColor(Color::Black);
			window.draw(m_verticalStrip);
		}
		if (m_playerNo == 2)
		{
			m_verticalStrip = RectangleShape(Vector2f(10, size.y));
			m_verticalStrip.setPosition(center.x - size.x / 2, center.y - size.y / 2);
			m_verticalStrip.setFillColor(Color::Black);
			window.draw(m_verticalStrip);
		}
	}
	else
	{
		if (m_playerNo == 2)
		{
			m_playerText.setPosition(500 + center.x - size.x / 2, center.y + size.y / 2 - size.y / 10 + 1);
			m_horisontalStrip.setPosition(m_playerText.getGlobalBounds().left+ m_playerText.getGlobalBounds().width, m_playerText.getGlobalBounds().top);
		}
	}

	if (m_playerNo == 1) window.draw(m_horisontalStrip);
	else {if (m_pvp) window.draw(m_horisontalStrip);}
	window.draw(m_playerText);
}


void FpsBar::update(float time)
{
	std::ostringstream fpsCounter;
	m_fps = 1000.f / time;
	fpsCounter << m_fps;
	m_fpsText.setString("FPS : " + fpsCounter.str());
}

void FpsBar::draw(RenderWindow& window)
{
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();
	m_fpsText.setCharacterSize(size.y / 25);
	m_fpsText.setFillColor(Color::White);
	m_fpsText.setPosition(5.f, 5.f);
	window.draw(m_fpsText);
}
