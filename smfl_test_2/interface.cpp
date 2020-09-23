#include "interface.h"

using namespace sf;

void GameInterface::create(RenderWindow& window, Font& FONT)
{
	m_font = FONT;
	m_center = window.getView().getCenter();
	m_size = window.getView().getSize();
	m_fontSize = m_size.y / 10;
	m_buttons.push_back(new Text("To main menu", m_font, m_fontSize));
	m_buttons.push_back(new Text("Continue", m_font, m_fontSize));
	m_Shape.setSize(Vector2f(m_buttons[0]->getGlobalBounds().width + 10, 15 + 3 *  m_buttons[0]->getGlobalBounds().height));
	m_Shape.setFillColor(Color::Black);
}

void GameInterface::composeButtons(std::vector<Text*> BUTTON)
{
	BUTTON[0]->setPosition(m_Shape.getPosition().x + 5, m_Shape.getPosition().y + 5);
	BUTTON[1]->setPosition(m_Shape.getPosition().x + 5, m_Shape.getPosition().y + 5 + 10 + BUTTON[1]->getGlobalBounds().height);
	/*for (int i = 1; i < BUTTON.size(); i++)
	{
		BUTTON[i]->setPosition(m_center.x - BUTTON[i]->getGlobalBounds().width / 2,
			m_fontSize / 2 + BUTTON[i - 1]->getGlobalBounds().height + BUTTON[i - 1]->getGlobalBounds().top);
	}*/
}

void GameInterface::update(RenderWindow& window)
{
	m_Shape.setPosition(Vector2f(window.getView().getCenter().x-m_Shape.getSize().x / 2,
		window.getView().getCenter().y - m_Shape.getSize().y / 2));
	composeButtons(m_buttons);
	//for (int i = 0; i < m_buttons.size(); i++) m_buttons[i]->setPosition(window.getView().getCenter());
}


void GameInterface::draw(RenderWindow& window, bool& EXIT)
{
	if (m_active) {
		update(window);
		window.setMouseCursorVisible(true);
		window.draw(m_Shape);
		for (int i = 0; i < m_buttons.size(); i++) 
		{ window.draw(*m_buttons[i]); }
		for (int i = 0; i < m_buttons.size(); i++)
		{
			m_buttons[i]->setFillColor(Color::White);
			if (IntRect(m_buttons[i]->getGlobalBounds()).contains(Mouse::getPosition(window))) {
				m_buttons[i]->setFillColor(Color::Blue);
				m_menuNum = i + 1;
			}
		}
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			switch (m_menuNum)
			{
			case 1: {
				m_active = false;
				EXIT = true;
				break; }
			case 2: {
				m_active = false;
				window.setMouseCursorVisible(false);
				//return false;
				break;
			}
			default:
				break;
			}
		}
	}
}

void GameInterface::callInGameMenu()
{
	m_active = true;
}

