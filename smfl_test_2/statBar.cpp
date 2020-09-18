#include "statBar.h"

using namespace sf;

statBar::statBar(Font& font, int PLAYER_NUMBER)
{
	playerNo = PLAYER_NUMBER;
	playerText.setFont(font);
}

void statBar::update(std::string name, int hp, int ammo)
{
	std::ostringstream playerHealthString;
	std::ostringstream playerAmmoString;
	playerHealthString << hp;
	playerAmmoString << ammo;
	playerText.setString(name + " HP : " + playerHealthString.str() + "\n" + name + " ammo : " + playerAmmoString.str());
}

void statBar::draw(RenderWindow& window)
{
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();
	playerText.setCharacterSize(size.y / 40);
	playerText.setFillColor(Color::White);
	horisontalStrip = RectangleShape(Vector2f(size.x, size.y / 10));
	horisontalStrip.setFillColor(Color::Black);
	playerText.setPosition(center.x - size.x / 2, center.y + size.y / 2 - size.y / 10 + 1);
	horisontalStrip.setPosition(center.x - size.x / 2, center.y + size.y / 2 - size.y / 10);
	if (playerNo == 1)
	{
		verticalStrip = RectangleShape(Vector2f(10, size.y));
		verticalStrip.setPosition(center.x + size.x / 2 - 10, center.y - size.y / 2);
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