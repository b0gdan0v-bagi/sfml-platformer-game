#include "interface.h"

using namespace sf;

void GameInterface::create(RenderWindow& window, Font& FONT)
{
	m_font = FONT;
	m_center = window.getView().getCenter();
	m_size = window.getView().getSize();
	m_fontSize = m_size.y / 10;
	buttons.push_back(new Text("To main menu", m_font, m_fontSize));
	buttons.push_back(new Text("Continue", m_font, m_fontSize));
	testShape.setSize(Vector2f(buttons[0]->getGlobalBounds().width + 10, 15 + 3 *  buttons[0]->getGlobalBounds().height));
	testShape.setFillColor(Color::Black);
}

void GameInterface::composeButtons(std::vector<Text*> BUTTON)
{
	BUTTON[0]->setPosition(testShape.getPosition().x + 5, testShape.getPosition().y + 5);
	BUTTON[1]->setPosition(testShape.getPosition().x + 5, testShape.getPosition().y + 5 + 10 + BUTTON[1]->getGlobalBounds().height);
	/*for (int i = 1; i < BUTTON.size(); i++)
	{
		BUTTON[i]->setPosition(m_center.x - BUTTON[i]->getGlobalBounds().width / 2,
			m_fontSize / 2 + BUTTON[i - 1]->getGlobalBounds().height + BUTTON[i - 1]->getGlobalBounds().top);
	}*/
}

void GameInterface::update(RenderWindow& window)
{
	testShape.setPosition(Vector2f(window.getView().getCenter().x-testShape.getSize().x / 2,
		window.getView().getCenter().y - testShape.getSize().y / 2));
	composeButtons(buttons);
	//for (int i = 0; i < buttons.size(); i++) buttons[i]->setPosition(window.getView().getCenter());
}


void GameInterface::draw(RenderWindow& window)
{
	
	window.draw(testShape);
	for (int i = 0; i < buttons.size(); i++) window.draw(*buttons[i]);
}