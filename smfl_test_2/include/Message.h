#ifndef MESSAGE_H
#define MESSAGE_H

#include "SFML/Graphics.hpp"

using namespace sf;

class Message
{
private:
	Text m_text; //message text
	RectangleShape m_shape; // background
	float m_timer, m_endTimer;
	float m_indent;
	int m_playerN;
	bool m_life;
public:

	Message(String Message, float endTimer, Font& font, RenderWindow& WINDOW
		, int playerN ,Color TextColor = Color::White, Color BackColor = Color::Black);
	void update(float time, float X, float Y);
	void draw(RenderWindow& window);
	int getPlayerN() { return m_playerN; }
	bool getLife() { return m_life; }
	void setLife(bool LIFE) { m_life = LIFE; }
};

#endif  MESSAGE_H