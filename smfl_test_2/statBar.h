#ifndef STATBAR_H
#define STATBAR_H

#include <SFML/Graphics.hpp>
//#include <ostream>
#include <sstream> 


using namespace sf;

class statBar
{
private:

	RectangleShape horisontalStrip, verticalStrip;
	Text playerText;
	int playerNo;
	float fps;
	bool fpsBool;


public:

	statBar(Font& font, int PLAYER_NUMBER = 0, bool FPSBOOL = false);

	void update(std::string name, int hp, int ammo, float time);

	void draw(RenderWindow& window);

};

#endif STATBAR_H

