#include "statBar.h"

using namespace sf;

statBar::statBar(Font& font, int PLAYER_NUMBER, bool FPSBOOL)
{
	playerNo = PLAYER_NUMBER;
	playerText.setFont(font);
	fpsBool = FPSBOOL;
}


void statBar::update(std::string name, int hp, int ammo, float time)
{
	std::ostringstream playerHealthString;
	std::ostringstream playerAmmoString;
	std::ostringstream fpsCounter;
	fps = 1000.f / time;
	playerHealthString << hp;
	playerAmmoString << ammo;
	fpsCounter << fps;
	if (fpsBool) playerText.setString(name + " HP : " + playerHealthString.str() + "\n" + name + " ammo : " + playerAmmoString.str() 
		+ "     FPS : " + fpsCounter.str());
	else playerText.setString(name + " HP : " + playerHealthString.str() + "\n" + name + " ammo : " + playerAmmoString.str());
}

void statBar::draw(RenderWindow& window)
{
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();
	playerText.setCharacterSize(size.y / 25);
	//playerText.setCharacterSize(20);
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