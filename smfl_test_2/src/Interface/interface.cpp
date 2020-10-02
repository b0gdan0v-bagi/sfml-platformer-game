#include "interface.h"
#include <iostream> 

using namespace sf;

void GameInterface::create(RenderWindow& window, Font& FONT)
{
	m_indent = 5;
	buttList.create(FONT, window, { "To main menu" ,"Continue","Restart" }, true, 15);
	buttList.setViewable(false);
	buttList.setPressable(true);
	m_defeatTextVisible = false;
}


void GameInterface::update(RenderWindow& window, int& STATE)
{
	if (m_active)
	{
		buttList.setViewable(m_active);
		buttList.setPressable(1, !m_defeatTextVisible); // dont show continue button if dead
		buttList.setViewable(1, !m_defeatTextVisible);
		buttList.updateCharSize(window);
		buttList.composeY(window, 0, -0.5);
		window.setMouseCursorVisible(true);
		m_menuNum = -1;
		buttList.checkMouseIntersects(m_menuNum, window, Color::Blue, Color::White);

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			switch (m_menuNum)
			{
			case 0: { // to main menu
				m_defeatTextVisible = false;
				m_active = false;
				STATE = 1; // go to main menu
				break; 
			}
			case 1: { // continue
				m_active = false;
				window.setMouseCursorVisible(false);
				//return false;
				STATE = 0; // continue
				break;
			}
			case 2: { // restart
				m_defeatTextVisible = false;
				m_active = false;
				window.setMouseCursorVisible(false);
				//return false;
				STATE = 2; // go to restart
				break;
			}
			default:
				break;
			}
		}
	}
}


void GameInterface::draw(RenderWindow& window)
{
	if (m_active) buttList.draw(window);
}





