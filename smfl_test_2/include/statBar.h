#ifndef STATBAR_H
#define STATBAR_H

#include <SFML/Graphics.hpp>
//#include <ostream>
#include <sstream> 


using namespace sf;

class statBar
{
private:

	RectangleShape m_horisontalStrip, m_verticalStrip;
	Text m_playerText;
	int m_playerNo;
	bool m_pvp;

public:

	statBar(Font& font, bool PVP, int PLAYER_NUMBER);

	void update(std::string name, int hp, int ammo, float time);
	void draw(RenderWindow& window);

};

class FpsBar
{
private:

	Text m_fpsText;
	float m_fps;

public:

	void setFont(Font& font) { m_fpsText.setFont(font); }
	void update(float time);
	void draw(RenderWindow& window);

};

#endif STATBAR_H

