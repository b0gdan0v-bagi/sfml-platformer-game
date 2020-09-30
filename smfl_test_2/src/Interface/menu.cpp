#include "menu.h"

using namespace sf;

void Menu::create(RenderWindow& window, Font& FONT, GlobalData &DATA)
{
	m_progVer = DATA.version;
	m_mailInfo = DATA.email;

	mainBut.create(FONT, window, { "New game : PVE" , "New game : PVP","Options","About", "Exit" }, false, 10);
	mainBut.composeY(window, window.getView().getSize().x / 2, -2 * window.getView().getSize().y/10);

	lvl.create(FONT, window, { "Choose your level","lvl 1", "lvl 2", "lvl 3" }, false, 10);
	lvl.composeY(window, window.getView().getSize().x / 2, -1 * window.getView().getSize().y / 10);
	lvl.setPressable(0, false);

	about.create(FONT, window, { "Game by Andey Bogdanov ", m_progVer,m_mailInfo, "back" },false,10);
	about.composeY(window, window.getView().getSize().x / 2, -1 * window.getView().getSize().y / 10);
	about.setPressable(false); 
	about.setPressable(3, true);

	option.create(FONT, window, { "Resolution:" ,"1280x720", "1920x1080", "3440x1440", }, false, 15);
	option.setPressable(0, false);
	option.composeX(window, -window.getView().getSize().x / 5, 50);
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

bool Menu::mainMenu(RenderWindow& window, GlobalData& data)
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
				if (levelMenu(window, data.numberLevel)) return true;
				break; }
			case 1: {
				isMenu = false;
				data.numberLevel = 101;
				return true;
				break;
			}
			case 2: {
				optionMenu(window, data);
				if (data.isChanged)
				{
					data.writeConfig();
					window.close();
					window.create(VideoMode(data.resolution.x, data.resolution.y), data.name + " " + data.version, Style::Close);
					data.setViewInterface();
					window.setView(data.viewInterface);
					//mainBut.composeY(window, window.getView().getSize().x / 2, -2 * window.getView().getSize().y / 10);
				}
				break;
			}
			case 3: {
				aboutMenu(window);

				break;
			}
			case 4: {
				return false;
				window.close();
				break; }
			default:
				break;
			}
		}
		mainBut.setViewable(isMenu);
		mainBut.setLineIndent(10);
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
		/*for (int i = 1; i <= DATA.numberLevelMax; i++)
		{
			std::ostringstream lvlNumber;
			lvlNumber << i;
			lvlMenuBut.push_back(new Text("lvl " + lvlNumber.str(), m_font, m_fontSize));
		}*/
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
			case 3: {return false; break; }
			default:
				break;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) return false;
		about.setViewable(isMenu);
		draw(window, about);
	}
}

bool Menu::optionMenu(RenderWindow& window, GlobalData& data)
{
	bool isMenu = true;
	while (Mouse::isButtonPressed(Mouse::Left)) {/* here is stop until mouse is unpressed */ }

	while (isMenu)
	{
		update(window, option);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			switch (m_menuNum)
			{
			case 1: {
				data.resolution.x = 1280;
				data.resolution.y = 720;
				data.isChanged = true;
				break;
			}
			case 2: {
				data.resolution.x = 1920;
				data.resolution.y = 1080;
				data.isChanged = true;
				break;
			}
			case 3: {
				data.isChanged = true;
				break;
			}
			default:
				break;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) return false;
		option.setViewable(isMenu);
		draw(window, option);
	}
}
