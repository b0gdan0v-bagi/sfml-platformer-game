#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "GlobalData.h"
#include <iostream>
#include <sstream>
using namespace sf; 

class Menu 
{
private:
	Font m_font;
	View m_menuView;
	
	float m_fontSize;
	Vector2f m_center, m_size; // for window.getView
	Text m_text;
	std::vector<Text*> mainMenuBut, lvlMenuBut, aboutMenuBut, inGameMenuBut;
	std::string m_progVer, m_mailInfo;
public:


	void create(RenderWindow& window, Font& FONT, GlobalData& data);
	void composeButtons(std::vector<Text*> BUTTON);
	void draw(RenderWindow& window, std::vector<Text*> BUTTON);
	void update(RenderWindow& window, int& MENUNUM, std::vector<Text*> BUTTON);
	bool mainMenu(RenderWindow& window, int& numberLevel);
	bool levelMenu(RenderWindow& window, int& numberLevel);
	bool aboutMenu(RenderWindow& window);
};


#endif MENU_H