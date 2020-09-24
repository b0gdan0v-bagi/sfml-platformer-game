#include "menu.h"


using namespace sf;



void Menu::create(RenderWindow& window, Font& FONT, GlobalData &DATA)
{
	m_font = FONT;
	m_progVer = DATA.version;
	m_mailInfo = DATA.email;
	m_center = window.getView().getCenter();
	m_size = window.getView().getSize();
	m_fontSize = m_size.y / 10;
	mainMenuBut.push_back(new Text("New game : PVE", m_font, m_fontSize));// menuNum = 1
	mainMenuBut.push_back(new Text("New game : PVP", m_font, m_fontSize));// menuNum = 2
	mainMenuBut.push_back(new Text("About", m_font, m_fontSize));         // menuNum = 3
	mainMenuBut.push_back(new Text("Exit", m_font, m_fontSize));          // menuNum = 4
	composeButtons(mainMenuBut);
	inGameMenuBut.push_back(new Text("Main menu", m_font, m_fontSize));   // menuNum = 1
	inGameMenuBut.push_back(new Text("Continue", m_font, m_fontSize));    // menuNum = 2
	composeButtons(inGameMenuBut);
	lvlMenuBut.push_back(new Text("Choose your level", m_font, m_fontSize));// menuNum = 1
	for (int i = 1; i <= DATA.numberLevelMax; i++)
	{
		std::ostringstream lvlNumber;
		lvlNumber << i;
		lvlMenuBut.push_back(new Text("lvl " + lvlNumber.str(), m_font, m_fontSize));
	}
	composeButtons(lvlMenuBut);
	aboutMenuBut.push_back(new Text("Game by Andey Bogdanov \n" + m_progVer + "\n" + m_mailInfo, m_font, m_fontSize));// menuNum = 1
	aboutMenuBut.push_back(new Text("back", m_font, m_fontSize));                                                     // menuNum = 2
	composeButtons(aboutMenuBut);
}

void Menu::composeButtons(std::vector<Text*> BUTTON)
{
	BUTTON[0]->setPosition(m_center.x - BUTTON[0]->getGlobalBounds().width / 2, m_fontSize);
	for (int i = 1; i < BUTTON.size(); i++)
	{
		BUTTON[i]->setPosition(m_center.x - BUTTON[i]->getGlobalBounds().width / 2,
			m_fontSize / 2 + BUTTON[i-1]->getGlobalBounds().height + BUTTON[i-1]->getGlobalBounds().top);
	}
}

void Menu::draw(RenderWindow& window, std::vector<Text*> BUTTON)
{
	for (int i = 0; i < BUTTON.size(); i++) window.draw(*BUTTON[i]);
	window.display();
}

void Menu::update(RenderWindow& window, int& MENUNUM, std::vector<Text*> BUTTON)
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();
	}
	window.setMouseCursorVisible(true);
	MENUNUM = 0;
	window.clear(Color(129, 181, 221));

	for (int i = 0; i < BUTTON.size(); i++)
	{
		BUTTON[i]->setFillColor(Color::White);
		if (IntRect(BUTTON[i]->getGlobalBounds()).contains(Mouse::getPosition(window))) {
			BUTTON[i]->setFillColor(Color::Blue);
			MENUNUM = i + 1;
		}
	}
}

bool Menu::mainMenu(RenderWindow& window, int& numberLevel)
{
	bool isMenu = true;
	int menuNum = 0;
	while (Mouse::isButtonPressed(Mouse::Left)) {/* here is stop until mouse is unpressed */ }
	while (isMenu)
	{
		update(window, menuNum, mainMenuBut);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			switch (menuNum)
			{
			case 1: {
				if (levelMenu(window, numberLevel)) return true;
				std::cout << "level menu ended!";
				std::cout << "isMenu = " << isMenu << "\n";
				//sleep(milliseconds(300)); 
				break; }
			case 2: {
				isMenu = false;
				numberLevel = 101;
				//sleep(milliseconds(300));
				return true;
				break;
			}
			case 3: {
				aboutMenu(window);
				break;
			}
			case 4: {
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
		draw(window, mainMenuBut);
	}
}

bool Menu::levelMenu(RenderWindow& window, int& numberLevel)
{
	bool isMenu = true;
	while (Mouse::isButtonPressed(Mouse::Left)) {/* here is stop until mouse is unpressed */ }

	int menuNum = 0;
	while (isMenu)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.setMouseCursorVisible(true);

		menuNum = 0;
		window.clear(Color(129, 181, 221));
		lvlMenuBut[0]->setFillColor(Color::White);
		for (int i = 1; i < lvlMenuBut.size(); i++)
		{
			lvlMenuBut[i]->setFillColor(Color::White);
			if (IntRect(lvlMenuBut[i]->getGlobalBounds()).contains(Mouse::getPosition(window))) {
				lvlMenuBut[i]->setFillColor(Color::Blue);
				menuNum = i;
				//std::cout << menuNum << "\n";
			}
		}
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			numberLevel = menuNum; // FOR TEST!

			if (menuNum != 0) return true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) return false;
		draw(window, lvlMenuBut);
	}
}

bool Menu::aboutMenu(RenderWindow& window)
{
	bool isMenu = true;
	while (Mouse::isButtonPressed(Mouse::Left)) {/* here is stop until mouse is unpressed */ }

	//int menuNum = 0;
	while (isMenu)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.setMouseCursorVisible(true);

		//menuNum = 0;
		window.clear(Color(129, 181, 221));
		aboutMenuBut[0]->setFillColor(Color::White);
		aboutMenuBut[1]->setFillColor(Color::White);
		if (IntRect(aboutMenuBut[1]->getGlobalBounds()).contains(Mouse::getPosition(window))) {
			aboutMenuBut[1]->setFillColor(Color::Blue);
			//menuNum = 1;
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				while (Mouse::isButtonPressed(Mouse::Left)) {/* here is stop until mouse is unpressed */ }
				return false;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) return false;
		draw(window, aboutMenuBut);
	}
}