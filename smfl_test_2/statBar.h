#ifndef STATBAR_H
#define STATBAR_H

#include <SFML/Graphics.hpp>

using namespace sf;

class statBar
{
public:
	RectangleShape horisontalStrip, verticalStrip;
	Text playerText;
	int playerNo;

	statBar(Font& font, int PLAYER_NUMBER = 0)
	{
		playerNo = PLAYER_NUMBER;
		playerText.setFont(font);
	}

	void update(std::string name,int hp, int ammo)
	{
		std::ostringstream playerHealthString;
		std::ostringstream playerAmmoString;
		playerHealthString << hp;
		playerAmmoString << ammo;
		playerText.setString(name + " HP : " + playerHealthString.str() + "\n" + name + " ammo : " + playerAmmoString.str());
	}

	void draw(RenderWindow& window)
	{
		Vector2f center = window.getView().getCenter();
		Vector2f size = window.getView().getSize();
		playerText.setCharacterSize(size.y / 40);
		if (Keyboard::isKeyPressed(Keyboard::X)) 
		{
			std::cout << "=========" << std::endl;
			std::cout << size.x << std::endl;
			std::cout << "=========" << std::endl;
		}
		//
		playerText.setFillColor(Color::White);
		horisontalStrip = RectangleShape(Vector2f(size.x, size.y / 10));
		horisontalStrip.setFillColor(Color::Black);
		playerText.setPosition(center.x - size.x / 2, center.y + size.y / 2 - size.y / 10 + 1);
		horisontalStrip.setPosition(center.x - size.x / 2, center.y + size.y / 2 - size.y / 10);
		if (playerNo == 1)
		{
			verticalStrip = RectangleShape(Vector2f(10, size.y));
			verticalStrip.setPosition(center.x + size.x / 2 - 10, center.y - size.y/2);
			verticalStrip.setFillColor(Color::Black);
			window.draw(verticalStrip);
		}
		if (playerNo == 2)
		{
			verticalStrip = RectangleShape(Vector2f(10, size.y));
			verticalStrip.setPosition(center.x - size.x / 2, center.y - size.y / 2);
			verticalStrip.setFillColor(Color::Black);
			window.draw(verticalStrip);
		}

		window.draw(horisontalStrip);
		window.draw(playerText);
	}

};

#endif STATBAR_H

