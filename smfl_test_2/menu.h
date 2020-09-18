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
	Menu() {}

	void setTextParam(Text& text, Text& prevText);
	void setTextParam(Text& text);
	void getCoords(RenderWindow& window);
	void setFont(Font& FONT);

	bool mainMenu(RenderWindow& window, int& numberLevel, bool isGameRunning = false);

	bool levelMenu(RenderWindow& window, int& numberLevel);

	bool aboutMenu(RenderWindow& window);
};


#endif MENU_H