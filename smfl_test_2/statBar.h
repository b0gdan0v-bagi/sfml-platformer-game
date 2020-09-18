#ifndef STATBAR_H
#define STATBAR_H

#include <SFML/Graphics.hpp>
//#include <ostream>
#include <sstream> 


using namespace sf;

class statBar
{
public:
	RectangleShape horisontalStrip, verticalStrip;
	Text playerText;
	int playerNo;


	statBar(Font& font, int PLAYER_NUMBER = 0);

	void update(std::string name, int hp, int ammo);

	void draw(RenderWindow& window);

};

#endif STATBAR_H

