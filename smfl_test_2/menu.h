#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
using namespace sf; 

class Menu 
{
public:
	Font font;
	View menuView;
	
	float fontSize;
	Vector2f center, size; // for window.getView
	Text text;
	Menu(RenderWindow& window)
	{
		font.loadFromFile("images/TimesNewRoman.ttf");
		center = window.getView().getCenter();
		size = window.getView().getSize();
		fontSize = size.x / 20;
	}

	void setTextParam(Text& text, Text& prevText)
	{
		text.setFont(font);
		text.setCharacterSize(fontSize);
		text.setPosition(center.x - text.getGlobalBounds().width / 2,
			fontSize + prevText.getGlobalBounds().height + prevText.getGlobalBounds().top);
	}
	void setTextParam(Text& text)
	{
		text.setFont(font); // start point at y axis
		text.setCharacterSize(fontSize);
		text.setPosition(center.x - text.getGlobalBounds().width / 2, fontSize);
	}

	bool mainMenu(RenderWindow& window, int& numberLevel, bool isGameRunning = false)
	{
		View view = window.getView();
		view.setCenter(0, 0);
		center = window.getView().getCenter();
		size = window.getView().getSize();
		view.setSize(size.x, size.y);
		std::vector<Text> menuIcon;

		menuIcon.push_back(text);
		menuIcon[0].setString("New game : PVE"); // menuNum = 1
		menuIcon.push_back(text);
		menuIcon[1].setString("New game : PVP"); // menuNum = 2
		menuIcon.push_back(text);
		menuIcon[2].setString("About"); // menuNum = 3
		menuIcon.push_back(text);
		menuIcon[3].setString("Exit"); // menuNum = 4
		if (isGameRunning) {
			menuIcon.push_back(text);
			menuIcon[4].setString("Continue"); // menuNum = 5
		}

		setTextParam(menuIcon[0]);
		for (int i = 1; i < menuIcon.size(); i++)
		{
			setTextParam(menuIcon[i], menuIcon[i - 1]);
		}
		bool isMenu = true;
		int menuNum = 0;
		while (Mouse::isButtonPressed(Mouse::Left)) {/* here is stop until mouse is unpressed */ }
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

			for (int i = 0; i < menuIcon.size(); i++)
			{
				menuIcon[i].setFillColor(Color::White);
				if (IntRect(menuIcon[i].getGlobalBounds()).contains(Mouse::getPosition(window))) {
					menuIcon[i].setFillColor(Color::Blue);
					menuNum = i+1;
				}
			}
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
					numberLevel = 3;
					sleep(milliseconds(300));
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
					sleep(milliseconds(300)); 
					break; }
				case 5: {
					return true;
					break; }
				default:
					break;
				}
			}
						
			for (int i = 0; i < menuIcon.size(); i++)
			{
				window.draw(menuIcon[i]);
			}
			
			window.display();
		}
	}

	bool levelMenu(RenderWindow& window, int& numberLevel)
	{
		std::vector<Text> menuIcon;
		menuIcon.push_back(text);
		menuIcon[0].setString("Choose your level"); 
		setTextParam(menuIcon[0]);
		for (int i = 1; i <= 4; i++)
		{
			std::ostringstream lvlNumber;
			lvlNumber << i;
			menuIcon.push_back(text);
			menuIcon[i].setString("lvl " + lvlNumber.str()); 
			setTextParam(menuIcon[i], menuIcon[i - 1]);
			//std::string buffer = menuIcon[i].getString();
			//std::cout << buffer << "\n";
		}
		bool isMenu = true;
		while (Mouse::isButtonPressed(Mouse::Left)) {/* here is stop until mouse is unpressed */}
		
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
			menuIcon[0].setFillColor(Color::White);
			for (int i = 1; i < menuIcon.size(); i++)
			{
				menuIcon[i].setFillColor(Color::White);
				if (IntRect(menuIcon[i].getGlobalBounds()).contains(Mouse::getPosition(window))) {
					menuIcon[i].setFillColor(Color::Blue);
					menuNum = i;
					//std::cout << menuNum << "\n";
				}
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				numberLevel = 1; // FOR TEST!

				if (menuNum != 0) return true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape)) return false;
			for (int i = 0; i < menuIcon.size(); i++)
			{
				window.draw(menuIcon[i]);
			}
			window.display();
		}
	}

	bool aboutMenu(RenderWindow& window)
	{
		std::vector<Text> menuIcon;
		menuIcon.push_back(text);
		menuIcon[0].setString("Game by Andey Bogdanov \n ver 0.2 \n bagizara@gmail.com");
		setTextParam(menuIcon[0]);
		menuIcon.push_back(text);
		menuIcon[1].setString("back");
		setTextParam(menuIcon[1], menuIcon[0]);

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
			menuIcon[0].setFillColor(Color::White);
			menuIcon[1].setFillColor(Color::White);
			if (IntRect(menuIcon[1].getGlobalBounds()).contains(Mouse::getPosition(window))) {
				menuIcon[1].setFillColor(Color::Blue);
				//menuNum = 1;
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					while (Mouse::isButtonPressed(Mouse::Left)) {/* here is stop until mouse is unpressed */ }
					return false;
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::Escape)) return false;
			for (int i = 0; i < menuIcon.size(); i++)
			{
				window.draw(menuIcon[i]);
			}
			window.display();
		}
	}
};


#endif MENU_H