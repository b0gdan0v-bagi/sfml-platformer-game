#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf; 

void menu(RenderWindow& window, Vector2f resolution, int& numberLevel) 
{
	Font font;
	font.loadFromFile("images/TimesNewRoman.ttf");
	Text about("", font, 50), menu1("", font, 50), menu2("", font, 50), menu3("", font, 50), menu4("", font, 50);
	Text lvl1("", font, 50), lvl2("", font, 50), back("", font, 50);
	about.setString("Game from Andrusha, ver 0.1");
	menu1.setString("New game : PVE");
	menu2.setString("About");
	menu3.setString("Exit");
	menu4.setString("New game : PVP");
	lvl1.setString("Level 1");
	lvl2.setString("Level 2");
	back.setString("Back to main menu");

	about.setPosition(resolution.x / 2 - about.getLocalBounds().width / 2, resolution.y / 2 - about.getLocalBounds().height / 2);

	Vector2f menu1Pos, menu2Pos, menu3Pos, menu4Pos;
	Vector2f lvl1Pos, lvl2Pos, backPos;

	bool isMenu = 1, levelMenu = false;
	int menuNum = 0;

	menu1Pos = Vector2f(resolution.x / 2 - menu1.getLocalBounds().width / 2, resolution.y / 2 - menu1.getLocalBounds().height / 2 - 300);
	menu2Pos = Vector2f(resolution.x / 2 - menu2.getLocalBounds().width / 2, resolution.y / 2 - menu2.getLocalBounds().height / 2);
	menu3Pos = Vector2f(resolution.x / 2 - menu3.getLocalBounds().width / 2, resolution.y / 2 - menu3.getLocalBounds().height / 2 + 150);
	menu4Pos = Vector2f(resolution.x / 2 - menu4.getLocalBounds().width / 2, resolution.y / 2 - menu4.getLocalBounds().height / 2 - 150);
	lvl1Pos = Vector2f(resolution.x / 2 - lvl1.getLocalBounds().width / 2, resolution.y / 2 - lvl1.getLocalBounds().height / 2 - 300);
	lvl2Pos = Vector2f(resolution.x / 2 - lvl2.getLocalBounds().width / 2, lvl1Pos.y + lvl1.getLocalBounds().height + 100);
	backPos = Vector2f(resolution.x / 2 - back.getLocalBounds().width / 2, lvl2Pos.y + lvl2.getLocalBounds().height + 100);

	menu1.setPosition(menu1Pos);
	menu2.setPosition(menu2Pos);
	menu3.setPosition(menu3Pos);
	menu4.setPosition(menu4Pos);
	lvl1.setPosition(lvl1Pos);
	lvl2.setPosition(lvl2Pos);
	back.setPosition(backPos);

	while (isMenu)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		menu1.setFillColor(Color::White);
		menu2.setFillColor(Color::White);
		menu3.setFillColor(Color::White);
		menu4.setFillColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));
		if (IntRect(menu1Pos.x, menu1Pos.y, menu1.getLocalBounds().width, menu1.getLocalBounds().height*2).contains(Mouse::getPosition(window))) 
		{ 
			menu1.setFillColor(Color::Blue);
			menuNum = 1; 
		}
		if (IntRect(menu2Pos.x, menu2Pos.y, menu2.getLocalBounds().width, menu2.getLocalBounds().height * 2).contains(Mouse::getPosition(window)))
		{ 
			menu2.setFillColor(Color::Blue);
			menuNum = 2; 
		}
		if (IntRect(menu3Pos.x, menu3Pos.y, menu3.getLocalBounds().width, menu3.getLocalBounds().height * 2).contains(Mouse::getPosition(window)))
		{ 
			menu3.setFillColor(Color::Blue);
			menuNum = 3; 
		}
		if (IntRect(menu4Pos.x, menu4Pos.y, menu4.getLocalBounds().width, menu4.getLocalBounds().height * 2).contains(Mouse::getPosition(window)))
		{
			menu4.setFillColor(Color::Blue);
			menuNum = 4;
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) 
			{ 
				levelMenu = true;
				sleep(milliseconds(300));
				//isMenu = false; 
				//numberLevel = 1; 
			}
			if (menuNum == 2) 
			{
				window.draw(about);
				window.display(); 
				while (!Keyboard::isKeyPressed(Keyboard::Escape)); 
				sleep(milliseconds(300));
			}
			if (menuNum == 3) 
			{
				numberLevel = 0;
				window.close(); 
				isMenu = false; 
				sleep(milliseconds(300));
			}
			if (menuNum == 4) 
			{ 
				isMenu = false; 
				numberLevel = 3; 
				sleep(milliseconds(300));
			}

		}

		while (levelMenu)
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}
			lvl1.setFillColor(Color::White);
			lvl2.setFillColor(Color::White);
			back.setFillColor(Color::White);
			menuNum = 0;
			window.clear(Color(129, 181, 221));
			if (IntRect(lvl1Pos.x, lvl1Pos.y, lvl1.getLocalBounds().width, lvl1.getLocalBounds().height * 2).contains(Mouse::getPosition(window)))
			{
				lvl1.setFillColor(Color::Blue);
				menuNum = 1;
			}
			if (IntRect(lvl2Pos.x, lvl2Pos.y, lvl2.getLocalBounds().width, lvl2.getLocalBounds().height * 2).contains(Mouse::getPosition(window)))
			{
				lvl2.setFillColor(Color::Blue);
				menuNum = 2;
			}
			if (IntRect(backPos.x, backPos.y, back.getLocalBounds().width, back.getLocalBounds().height * 2).contains(Mouse::getPosition(window)))
			{
				back.setFillColor(Color::Blue);
				menuNum = 3;
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape)) { levelMenu = false; }
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (menuNum == 1)
				{
					levelMenu = false;
					isMenu = false; 
					numberLevel = 1; 

				}
				if (menuNum == 2)
				{
					levelMenu = false;
					isMenu = false;
					numberLevel = 2;
				}
				if (menuNum == 3)
				{
					levelMenu = false;
					isMenu = true;
					sleep(milliseconds(300));
				}
			}
			
			window.draw(lvl1);
			window.draw(lvl2);
			window.draw(back);
			window.display();
		}

		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.draw(menu4);

		window.display();
	}
}