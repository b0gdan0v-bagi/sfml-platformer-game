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
	option["resolution"].create(FONT, window, { "Resolution:" ,"1280x720", "1920x1080", "3440x1440", }, false, 15);
	option["resolution"].setPressable(0, false);
	option["apply"].create(FONT, window, { "Apply" ,"  back", }, false, 15);
	option["apply"].setViewAndPressable(0, false);
	option["showfps"].create(FONT, window, { "Show fps :      ", "yes", "no" }, false, 15);
	option["showfps"].setPressable(0, false);
	option["players_pve"].create(FONT, window, { "Players PVE :      ", " 1 ", " 2 " }, false, 15);
	option["players_pve"].setPressable(0, false);
	option["players_names"].create(FONT, window, { "Names :      ", DATA.playersName[0], DATA.playersName[1] }, false, 15);
	option["players_names"].setPressable(0, false);
	option["input_text"].create(FONT, window, { "Enter your name and press ENTER" }, false, 15);
	option["input_text"].setViewAndPressable(0, false);
	option["players_models"].create(FONT, window, { "models : Player 1 :   ", DATA.playersModel[0], "    Player 2 :    " , DATA.playersModel[1] }, false, 15);
	option["players_models"].setPressable(0, false);
	option["players_models"].setPressable(2, false);
	DATA.volumeToString();
	option["sound"].create(FONT, window, { "Sound : music :   ", DATA.musicVolumeString, "    interactions :    " , DATA.sndVolumeString }, false, 15);
	option["sound"].setPressable(0, false);
	option["sound"].setPressable(2, false);
	DATA.setContersToString();
	levelChange.create(FONT, window, { "Congratulations!",DATA.nOfKilledStr,DATA.nOfShotsStr,DATA.nOfBotGainedStr,"To main menu","continue" }, false, 10);
	levelChange.setPressable(0, false);
	levelChange.setPressable(1, false);
	levelChange.setPressable(2, false);
	levelChange.setPressable(3, false);

	composeAll(window);

	if (DATA.resolution.x == 1280) option["resolution"].switchBackgroundTo(1);
	if (DATA.resolution.x == 1920) option["resolution"].switchBackgroundTo(2);
	if (DATA.resolution.x == 3440) option["resolution"].switchBackgroundTo(3);
	if (DATA.showFps) option["showfps"].switchBackgroundTo(1);
	else option["showfps"].switchBackgroundTo(2);
	switch (DATA.playersPVE)
	{
	case 2: {option["players_pve"].switchBackgroundTo(2); break; }
	default:{ option["players_pve"].switchBackgroundTo(1); break; }
	}
}

void Menu::composeAll(RenderWindow& window)
{
	window.setView(m_menuView);
	m_menuView.setSize(Vector2f(window.getSize()));
	m_menuView.setCenter(window.getSize().x / 2, window.getSize().y / 2);

	mainBut.updateCharSize(window);
	lvl.updateCharSize(window);
	about.updateCharSize(window);
	levelChange.updateCharSize(window);
	for (auto op = option.begin(); op!=option.end(); op++) (*op).second.updateCharSize(window);

	mainBut.composeY(window, 0, -0.95);
	lvl.composeY(window, 0, -0.95);
	about.composeY(window, 0, -0.95);
	levelChange.composeY(window, 0, -0.9);
	option["resolution"].composeX(window, -1, -0.95);
	option["apply"].composeX(window, -1, 0.1);
	option["showfps"].composeX(window, -1, -0.80);
	option["players_pve"].composeX(window, -1, -0.65);
	option["players_names"].composeX(window, -1, -0.5);
	option["players_models"].composeX(window, -1, -0.3);
	option["sound"].composeX(window, -1, -0.1);
	option["input_text"].composeX(window, -0.8, 0.3);
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
			case 0: { m_intersectSound.play();
				if (levelMenu(window, data)) return true;
				break; }
			case 1: { m_intersectSound.play();
				isMenu = false;
				data.numberLevel = 101;
				return true;
				break;
			}
			case 2: { m_intersectSound.play();
				if (optionMenu(window, data)) 
				{
					composeAll(window);
				}
				break;
			}
			case 3: { m_intersectSound.play();
				aboutMenu(window);

				break;
			}
			case 4: { m_intersectSound.play();
				while (m_intersectSound.getStatus() == 2) {} // wait for playing sound
				return false;
				window.close();
				break; }
			default:
				break;
			}
			//std::cout << Mouse::getPosition(window).x << " " << Mouse::getPosition(window).y << "\n";
			//std::cout << "view center : " << window.getView().getCenter().x << "\n";
		}
		/*std::ostringstream test1, test2;
		//test1 << Mouse::getPosition(window).x;
		//test2 << Mouse::getPosition(window).y;
		test1 << window.mapPixelToCoords(Mouse::getPosition(window)).x;
		test2 << window.mapPixelToCoords(Mouse::getPosition(window)).y;
		Text t;
		t.setString("mouse : " + test1.str() + " " + test2.str());
		Font f;
		f.loadFromFile("resourses/TimesNewRoman.ttf");
		t.setFont(f);
		window.draw(t);*/
		mainBut.setViewable(isMenu);
		draw(window, mainBut);
		
	}
	return false;
}

bool Menu::levelMenu(RenderWindow& window, GlobalData& data)
{
	bool isMenu = true;
	while (Mouse::isButtonPressed(Mouse::Left)) {/* here is stop until mouse is unpressed */ }

	while (isMenu)
	{
		update(window, lvl);
		for (int i = 1; i <= data.numberLevelMax; i++)
		{
			if (i <= data.numberLevelAvailiable) lvl.setViewAndPressable(i, true);
			else lvl.setViewAndPressable(i, false);
		}
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			data.numberLevel = m_menuNum; 
			if ((m_menuNum != 0) && (m_menuNum != -1)) {
				m_intersectSound.play(); return true;
			}
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
			case 3: {m_intersectSound.play(); return false; break; }
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
	int nameEntered = 0;
	std::string nameInput = "";
	Vector2f resolutionBuff;
	while (isMenu)
	{
		Event event;
		while (window.pollEvent(event))
		{

			if (event.type == Event::Closed)
				window.close();
			if (nameEntered != 0)
			{
				if (event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode < 128)
					{
						nameInput += event.text.unicode;
						option["players_names"].setButtonString(nameEntered, nameInput);
						option["players_names"].composeX(window, -1, -0.5);
					}
				}
				if (event.type == sf::Event::KeyPressed)
					if (event.key.code == Keyboard::Enter)
					{
						option["apply"].setViewAndPressable(0, true);
						data.playersName[nameEntered-1] = nameInput;
						nameEntered = 0;
						nameInput.clear();
						option["players_names"].switchBackgroundTo();
						option["input_text"].setViewable(0, false);
						
					}
			}
		}
		window.setMouseCursorVisible(true);
		for (auto op = option.begin(); op != option.end(); op++)
		{
			optN[(*op).first] = -1;
			(*op).second.checkMouseIntersects(optN[(*op).first], window, Color::Blue, Color::White);
		}
		window.clear(Color(129, 181, 221));
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			switch (optN["resolution"])
			{
			case 1: { m_intersectSound.play();
				resolutionBuff.x = 1280;
				resolutionBuff.y = 720;
				if (!option["resolution"].getBackgroundViewable(1)) { option["apply"].setViewAndPressable(0, true); resolutionChanged = true; }
				option["resolution"].switchBackgroundTo(1);
				data.isChanged = true;
				break;
			}
			case 2: { m_intersectSound.play();
				resolutionBuff.x = 1920;
				resolutionBuff.y = 1080;
				if (!option["resolution"].getBackgroundViewable(2)) { option["apply"].setViewAndPressable(0, true); resolutionChanged = true; }
				option["resolution"].switchBackgroundTo(2);
				data.isChanged = true;
				break;
			}
			case 3: { m_intersectSound.play();
				resolutionBuff.x = 3440;
				resolutionBuff.y = 1440;
				if (!option["resolution"].getBackgroundViewable(3)) { option["apply"].setViewAndPressable(0, true); resolutionChanged = true; }
				option["resolution"].switchBackgroundTo(3);
				
				break;
			}
			default:
				break;
			}
			switch (optN["apply"])
			{
			case 0: {
				m_intersectSound.play();
				option["apply"].setViewAndPressable(0, false);
				
				if (resolutionChanged)
				{
					data.resolution = resolutionBuff;
					window.close();
					window.create(VideoMode(data.resolution.x, data.resolution.y), data.name + " " + data.version, Style::Close);
					window.setMouseCursorGrabbed(true);
					window.setView(data.viewInterface);
					data.setViewInterface();
					composeAll(window);
					resolutionChanged = false;
				}
				data.writeConfig();
				return true;
				break;
			}
			case 1: {
				m_intersectSound.play();
				option["apply"].setViewAndPressable(0, false);
				return false;
				break;
			}
			default:
				break;
			}
			switch (optN["showfps"])
			{
			case 1: { m_intersectSound.play();
				data.showFps = true;
				if (!option["showfps"].getBackgroundViewable(1)) option["apply"].setViewAndPressable(0, true);
				option["showfps"].switchBackgroundTo(1);
				break;
			}
			case 2: { m_intersectSound.play();
				data.showFps = false;
				if (!option["showfps"].getBackgroundViewable(2)) option["apply"].setViewAndPressable(0, true);
				option["showfps"].switchBackgroundTo(2);
				break;
			}
			default:
				break;
			}
			switch (optN["players_pve"])
			{
			case 1: { m_intersectSound.play();
				data.playersPVE = 1;
				if (!option["players_pve"].getBackgroundViewable(1)) option["apply"].setViewAndPressable(0, true);
				option["players_pve"].switchBackgroundTo(1);
				break;
			}
			case 2: { m_intersectSound.play();
				data.playersPVE = 2;
				if (!option["players_pve"].getBackgroundViewable(2)) option["apply"].setViewAndPressable(0, true);
				option["players_pve"].switchBackgroundTo(2);
				break;
			}
			default:
				break;
			}
			switch (optN["players_names"])
			{
			case 1: { m_intersectSound.play();
				nameEntered = 1;
				option["players_names"].switchBackgroundTo(1);
				option["players_names"].setButtonString(1, "_");
				option["input_text"].setViewable(0, true);
				break;
			}
			case 2: { m_intersectSound.play();
				nameEntered = 2;
				option["players_names"].switchBackgroundTo(2);
				option["players_names"].setButtonString(2, "_");
				option["input_text"].setViewable(0, true);
				break;
			}
			default: 
				break; 
			}
			switch (optN["players_models"])
			{
			case 1: { m_intersectSound.play();
				while (Mouse::isButtonPressed(Mouse::Left)) {/* here is stop until mouse is unpressed */ }
				if (data.playersModel[0] == "player") data.playersModel[0] = "char";
				else data.playersModel[0] = "player";
				option["players_models"].setButtonString(1, data.playersModel[0]);
				option["apply"].setViewAndPressable(0, true);
				break;
			}
			case 3: { m_intersectSound.play();
				while (Mouse::isButtonPressed(Mouse::Left)) {/* here is stop until mouse is unpressed */ }
				if (data.playersModel[1] == "player") data.playersModel[1] = "char";
				else data.playersModel[1] = "player";
				option["players_models"].setButtonString(3, data.playersModel[1]);
				option["apply"].setViewAndPressable(0, true);
				break;
			}
			default:
				break;
			}
			switch (optN["sound"])
			{
			case 1: { m_intersectSound.play();
				while (Mouse::isButtonPressed(Mouse::Left)) {/* here is stop until mouse is unpressed */ }
				
				data.musicVolume += 15;
				if (data.musicVolume >= 100) data.musicVolume = 0;
				data.volumeToString();
				option["sound"].setButtonString(1, data.musicVolumeString);
				option["apply"].setViewAndPressable(0, true);
				break;
			}
			case 3: { m_intersectSound.play();
				while (Mouse::isButtonPressed(Mouse::Left)) {/* here is stop until mouse is unpressed */ }
				data.sndVolume += 15;
				if (data.sndVolume >= 100) data.sndVolume = 0;
				data.volumeToString();
				option["sound"].setButtonString(3, data.sndVolumeString);
				option["apply"].setViewAndPressable(0, true);
				break;
			}
			default:
				break;
			}
		}
		option["apply"].composeX(window, -1, 0.1);
		if (Keyboard::isKeyPressed(Keyboard::Escape)) return false;
		for (auto op = option.begin(); op != option.end(); op++)
		{
			(*op).second.setViewable(isMenu);
			(*op).second.draw(window);
		}
		window.display();
	}
}

bool Menu::levelChangeMenu(RenderWindow& window, GlobalData& data)
{
	window.setView(m_menuView);
	bool isMenu = true;
	bool isFinal;
	while (Mouse::isButtonPressed(Mouse::Left)) {/* here is stop until mouse is unpressed */ }
	if (data.numberLevel > data.numberLevelMax)
	{
		isFinal = true;
		//levelChange.setViewAndPressable(2, false);
		data.numberLevel = data.numberLevelMax;
		// bla bla bla
	}
	else isFinal = false;
	data.setContersToString(isFinal);
	levelChange.setButtonString(1, data.nOfKilledStr);
	levelChange.setButtonString(2, data.nOfShotsStr);
	levelChange.setButtonString(3, data.nOfBotGainedStr);
	while (isMenu)
	{
		update(window, levelChange);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			switch (m_menuNum)
			{
			case 4: { m_intersectSound.play();
				return false;
				break;
			}
			case 5: { m_intersectSound.play();
				return true;
				break;
			}
			default:
				break;
			}
		}
		levelChange.setViewable(isMenu);
		draw(window, levelChange);

	}
	return false;
}
