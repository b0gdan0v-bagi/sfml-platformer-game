#include "interface.h"
#include <iostream> 

using namespace sf;

void GameInterface::create(RenderWindow& window, Font& FONT)
{
	m_indent = 5;
	m_font = FONT;
	m_center = window.getView().getCenter();
	m_size = window.getView().getSize();
	m_fontSize = m_size.y / 10;
	m_buttons.push_back(new Button("To main menu", m_font, m_fontSize)); //id 0 
	m_buttons.push_back(new Button("Continue", m_font, m_fontSize));     //id 1
	m_buttons.push_back(new Button("WASTED", m_font, m_fontSize * 2));   //id 2	
	m_buttons[2]->setFillColor(Color::Red);
	m_buttons[2]->canPressed = false;
	m_buttons[2]->viewable = false;
	m_buttons.push_back(new Button("Restart", m_font, m_fontSize));       //id 3
	m_buttons[3]->canPressed = false;
	m_buttons[3]->viewable = false;
	m_defeatTextVisible = false;
	m_Shape.setFillColor(Color::Black);
}


void GameInterface::composeButtons(std::vector<Button*> BUTTON)
{
	BUTTON[0]->setPosition(m_Shape.getPosition().x + 5, m_Shape.getPosition().y + 5);
	BUTTON[1]->setPosition(m_Shape.getPosition().x + 5, m_Shape.getPosition().y + 2 * m_indent + BUTTON[1]->getSize().y);
	BUTTON[2]->setPosition(m_Shape.getPosition().x + m_Shape.getGlobalBounds().width / 2 - BUTTON[2]->getSize().x / 2,
		m_Shape.getPosition().y - m_fontSize * 2 - BUTTON[2]->getSize().y);
	BUTTON[3]->setPosition(BUTTON[1]->getPosition());
}

void GameInterface::update(RenderWindow& window, bool& EXIT)
{
	if (m_active)
	{
		m_Shape.setPosition(Vector2f(window.getView().getCenter().x - m_Shape.getSize().x / 2,
			window.getView().getCenter().y - m_Shape.getSize().y / 2));
		composeButtons(m_buttons);
		int count = 1;
		for (int i = 0; i < m_buttons.size(); ++i)
		{
			if ((m_buttons[i]->viewable) && (i!=2)) count++;
		}
		m_Shape.setSize(Vector2f(m_buttons[0]->getSize().x + 2 * m_indent, count * (m_indent + m_buttons[0]->getSize().y)));
		window.setMouseCursorVisible(true);

		if (m_defeatTextVisible) {
			m_buttons[2]->viewable = true;
			m_buttons[3]->viewable = true;
			m_buttons[3]->canPressed = true;
			m_buttons[1]->viewable = false;
			m_buttons[1]->canPressed = false;
		}
		else
		{
			m_buttons[2]->viewable = false;
			m_buttons[3]->viewable = false;
			m_buttons[3]->canPressed = false;
			m_buttons[1]->viewable = true;
			m_buttons[1]->canPressed = true;
		}
		for (int i = 0; i < m_buttons.size(); ++i)
		{
			if (m_buttons[i]->canPressed) m_buttons[i]->setFillColor(Color::White);
			if (IntRect(m_buttons[i]->getGlobalBounds()).contains(Mouse::getPosition(window))) {
				if (m_buttons[i]->canPressed)
				{
					m_buttons[i]->setFillColor(Color::Blue);
					m_menuNum = i;
				}
			}
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			switch (m_menuNum)
			{
			case 0: { // to main menu
				m_defeatTextVisible = false;
				m_active = false;
				EXIT = true;
				break; 
			}
			case 1: { // continue
				m_active = false;
				window.setMouseCursorVisible(false);
				//return false;
				break;
			}
			case 3: { // restart
				m_defeatTextVisible = false;
				m_active = false;
				window.setMouseCursorVisible(false);
				//return false;
				EXIT = true;
				break;
			}
			default:
				break;
			}
		}
		draw(window);
	}
}


void GameInterface::draw(RenderWindow& window)
{
		window.draw(m_Shape);
		for (int i = 0; i < m_buttons.size(); ++i) 
		{ 
			if (m_buttons[i]->viewable) window.draw(*m_buttons[i]);			
		}
}





