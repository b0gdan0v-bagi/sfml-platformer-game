#include "Message.h"

using namespace sf;

Message::Message(String MESSAGE, float endTimer, Font& font, RenderWindow& WINDOW,
	int playerN, Color TextColor, Color BackColor)
{
	m_playerN = playerN;
	m_indent = 5;
	button = new Button(MESSAGE, font, WINDOW);
	m_timer = 0;
	m_endTimer = endTimer;
	m_life = true;
}

void Message::update(float time, float X, float Y)
{
	m_timer += time;
	if (m_timer > m_endTimer) m_life = false;
	button->update(X, Y);
}

void Message::draw(RenderWindow& window)
{
	button->draw(window);
}
