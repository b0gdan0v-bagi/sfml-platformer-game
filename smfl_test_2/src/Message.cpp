#include "Message.h"

using namespace sf;

Message::Message(String MESSAGE, float endTimer, Font& font, RenderWindow& WINDOW,
	int playerN, Color TextColor, Color BackColor)
{
	m_playerN = playerN;
	m_indent = 5;
	m_text.setFont(font);
	m_text.setFillColor(TextColor);
	m_text.setCharacterSize(WINDOW.getView().getSize().y / 25); // scale for different resolution
	m_text.setString(MESSAGE);
	m_backGround.setFillColor(BackColor);
	m_backGround.setSize(Vector2f(m_text.getGlobalBounds().width + m_indent * 2, m_text.getGlobalBounds().height + m_indent * 2));
	m_timer = 0;
	m_endTimer = endTimer;
	m_life = true;
}

void Message::update(float time, float X, float Y)
{
	m_timer += time;
	if (m_timer > m_endTimer) m_life = false;
	m_text.setPosition(X + m_indent, Y + m_indent);
	m_backGround.setPosition(X, Y);

}

void Message::draw(RenderWindow& window)
{
	//window.draw(m_backGround);
	window.draw(m_text);
	
}
