#include "menu.h"

using namespace sf;

void Menu::create(RenderWindow& window, Font& FONT, GlobalData &DATA)
{
	window.setView(m_menuView);
	m_menuView.setSize(Vector2f(window.getSize()));
	m_menuView.setCenter(window.getSize().x / 2, window.getSize().y / 2);
	m_progVer = DATA.version;
	m_mailInfo = DATA.email;
	mainBut.create(FONT, window, { "New game : PVE" , "New game : PVP","Options","About", "Exit" }, false, 10);
	lvl.create(FONT, window, { "Choose your level","lvl 1", "lvl 2", "lvl 3" }, false, 10);
	lvl.setPressable(0, false);
	about.create(FONT, window, { "Game by Andey Bogdanov ", DATA.version, DATA.email, "back" },false,10);
	about.setPressable(false); 
	about.setPressable(3, true);
	option.push_back(new ButtonList(FONT, window, { "Resolution:" ,"1280x720", "1920x1080", "3440x1440", }, false, 15));
	option[0]->setPressable(0, false);
	option.push_back(new ButtonList(FONT, window, { "Apply" ,"  back", }, false, 15));
	option[1]->setPressable(0, false);
	option.push_back(new ButtonList(FONT, window, { "Show fps :      ", "yes", "no" }, false, 15));
	option[2]->setPressable(0, false);

	composeAll(window);

	optN.resize(option.size());

	if (DATA.resolution.x == 1280) option[0]->switchBackgroundTo(1);
	if (DATA.resolution.x == 1920) option[0]->switchBackgroundTo(2);
	if (DATA.resolution.x == 3440) option[0]->switchBackgroundTo(3);
	if (DATA.showFps) option[2]->switchBackgroundTo(1);
	else option[2]->switchBackgroundTo(2);
}

void Menu::composeAll(RenderWindow& window)
{
	window.setView(m_menuView);
	m_menuView.setSize(Vector2f(window.getSize()));
	m_menuView.setCenter(window.getSize().x / 2, window.getSize().y / 2);

	mainBut.updateCharSize(window);
	lvl.updateCharSize(window);
	about.updateCharSize(window);
	for (std::vector<ButtonList*>::iterator op = option.begin();op!=option.end();op++) (*op)->updateCharSize(window);

	mainBut.composeY(window, 0, -0.95);
	lvl.composeY(window, 0, -0.95);
	about.composeY(window, 0, -0.95);
	option[0]->composeX(window, -1, -0.95);
	option[1]->composeX(window, -1, 0);
	option[2]->composeX(window, -1, -0.80);
}


void Menu::draw(RenderWindow& window, ButtonList& butList)
{
	butList.draw(window, m_menuView);
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
	m_menuNum = -1;
	butList.checkMouseIntersects(m_menuNum, window, Color::Blue, Color::White);
	window.clear(Color(129, 181, 221));
}

bool Menu::mainMenu(RenderWindow& window, GlobalData& data)
{
	window.setView(m_menuView);
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
				if (optionMenu(window, data)) 
				{
					composeAll(window);
				}
				
				if (data.isChanged)
				{

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
			//std::cout << Mouse::getPosition(window).x << " " << Mouse::getPosition(window).y << "\n";
			//std::cout << "view center : " << window.getView().getCenter().x << "\n";
		}
		std::ostringstream test1, test2;
		test1 << Mouse::getPosition(window).x;
		test2 << Mouse::getPosition(window).y;
		Text t;
		t.setString("mouse : " + test1.str() + " " + test2.str());
		Font f;
		f.loadFromFile("resourses/TimesNewRoman.ttf");
		t.setFont(f);
		window.draw(t);
		mainBut.setViewable(isMenu);
		//mainBut.setLineIndent(10);
		draw(window, mainBut);
		
	}
	return false;
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
			if ((m_menuNum != 0) && (m_menuNum != -1))  return true;
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
	bool resolutionChanged = false;
	Vector2f resolutionBuff;
	while (isMenu)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.setMouseCursorVisible(true);
		for (int i = 0; i < optN.size(); ++i)
		{
			optN[i] = -1;
			option[i]->checkMouseIntersects(optN[i], window, Color::Blue, Color::White);
		}
		window.clear(Color(129, 181, 221));
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			switch (optN[0])
			{
			case 1: {
				resolutionBuff.x = 1280;
				resolutionBuff.y = 720;
				if (!option[0]->getBackgroundViewable(1)) { option[1]->setPressable(0, true); resolutionChanged = true; }
				option[0]->switchBackgroundTo(1);
				data.isChanged = true;
				break;
			}
			case 2: {
				resolutionBuff.x = 1920;
				resolutionBuff.y = 1080;
				if (!option[0]->getBackgroundViewable(2)) { option[1]->setPressable(0, true); resolutionChanged = true; }
				option[0]->switchBackgroundTo(2);
				data.isChanged = true;
				break;
			}
			case 3: {
				resolutionBuff.x = 3440;
				resolutionBuff.y = 1440;
				if (!option[0]->getBackgroundViewable(3)) { option[1]->setPressable(0, true); resolutionChanged = true; }
				option[0]->switchBackgroundTo(3);
				
				break;
			}
			default:
				break;
			}
			switch (optN[1])
			{
			case 0: {
				
				option[1]->setPressable(0, false);
				data.writeConfig();
				if (resolutionChanged)
				{
					data.resolution = resolutionBuff;
					window.close();
					window.create(VideoMode(data.resolution.x, data.resolution.y), data.name + " " + data.version, Style::Close);
					window.setView(data.viewInterface);
					data.setViewInterface();
					composeAll(window);
					resolutionChanged = false;
				}
				return true;
				break;
			}
			case 1: {
				option[1]->setPressable(0, false);
				return false;
				break;
			}
			default:
				break;
			}
			switch (optN[2])
			{
			case 1: {
				data.showFps = true;
				if (!option[2]->getBackgroundViewable(1)) option[1]->setPressable(0, true);
				option[2]->switchBackgroundTo(1);
				break;
			}
			case 2: {
				data.showFps = false;
				if (!option[2]->getBackgroundViewable(2)) option[1]->setPressable(0, true);
				option[2]->switchBackgroundTo(2);
				break;
			}
			default:
				break;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) return false;
		for (std::vector<ButtonList*>::iterator op = option.begin(); op != option.end(); op++)
		{
			(*op)->setViewable(isMenu);
			(*op)->draw(window);
		}
		window.display();
	}
}
