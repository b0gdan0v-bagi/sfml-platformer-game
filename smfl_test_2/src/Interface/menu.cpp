#include "menu.h"


using namespace sf;



void Menu::create(RenderWindow& window, Font& FONT, GlobalData &DATA)
{
	m_progVer = DATA.version;
	m_mailInfo = DATA.email;

	mainBut.create(FONT, window, { "New game : PVE" , "New game : PVP","About", "Exit" }, false, 10);
	//mainBut.setLineIndent(20);
	mainBut.composeY(window, window.getView().getSize().x / 2, window.getView().getSize().y / 10);
	/*lvlMenuBut.push_back(new Text("Choose your level", m_font, m_fontSize));// menuNum = 1
	for (int i = 1; i <= DATA.numberLevelMax; i++)
	{
		std::ostringstream lvlNumber;
		lvlNumber << i;
		lvlMenuBut.push_back(new Text("lvl " + lvlNumber.str(), m_font, m_fontSize));
	}*/
	lvl.create(FONT, window, { "Choose your level","lvl 1", "lvl 2", "lvl 3" }, false, 10);
	lvl.composeY(window, window.getView().getSize().x / 2, window.getView().getSize().y / 10);
	lvl.setPressable(0, false);

	about.create(FONT, window, { "Game by Andey Bogdanov ", m_progVer , "back" },false,10);
	about.composeY(window, window.getView().getSize().x / 2, window.getView().getSize().y / 10);

	about.setPressable(false); 
	about.setPressable(2, true);

}


void Menu::draw(RenderWindow& window, ButtonList& butList)
{
	butList.draw(window);
	window.display();
}

void Menu::update(RenderWindow& window, ButtonList& butList)
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();
	}
	window.setMouseCursorVisible(true);
	m_menuNum = 0;
	butList.checkMouseIntersects(m_menuNum, window, Color::Blue, Color::White);
	window.clear(Color(129, 181, 221));
}

bool Menu::mainMenu(RenderWindow& window, int& numberLevel)
{
	bool isMenu = true;
	while (Mouse::isButtonPressed(Mouse::Left)) {/* here is stop until mouse is unpressed */ }
	while (isMenu)
	{
		update(window, mainBut);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			switch (m_menuNum)
			{
			case 0: {
				if (levelMenu(window, numberLevel)) return true;
				std::cout << "level menu ended!";
				std::cout << "isMenu = " << isMenu << "\n";
				//sleep(milliseconds(300)); 
				break; }
			case 1: {
				isMenu = false;
				numberLevel = 101;
				//sleep(milliseconds(300));
				return true;
				break;
			}
			case 2: {
				aboutMenu(window);
				break;
			}
			case 3: {
				return false;
				numberLevel = 0;
				window.close();
				isMenu = false;
				//sleep(milliseconds(300));
				break; }
			default:
				break;
			}
		}
		mainBut.setViewable(isMenu);
		draw(window, mainBut);
	}
}

bool Menu::levelMenu(RenderWindow& window, int& numberLevel)
{
	bool isMenu = true;
	while (Mouse::isButtonPressed(Mouse::Left)) {/* here is stop until mouse is unpressed */ }

	while (isMenu)
	{
		update(window, lvl);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			numberLevel = m_menuNum; 
			if (m_menuNum != 0) return true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) return false;
		lvl.setViewable(isMenu);
		draw(window, lvl);
	}
}

bool Menu::aboutMenu(RenderWindow& window)
{
	bool isMenu = true;
	while (Mouse::isButtonPressed(Mouse::Left)) {/* here is stop until mouse is unpressed */ }

	while (isMenu)
	{
		update(window, about);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			while (Mouse::isButtonPressed(Mouse::Left)) {/* here is stop until mouse is unpressed */ };
			switch (m_menuNum)
			{
			case 2: {return false; break; }
			default:
				break;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) return false;
		about.setViewable(isMenu);
		draw(window, about);
	}
}