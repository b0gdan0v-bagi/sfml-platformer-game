#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "GlobalData.h"
#include "Button.h"
#include <iostream>
#include <sstream>
using namespace sf; 


class Menu 
{
private:
	View m_menuView;
	int m_menuNum;
	Text m_text;
	ButtonList about, mainBut, lvl, option;
	std::string m_progVer, m_mailInfo;
	void draw(RenderWindow& window, ButtonList& butList);
	void update(RenderWindow& window, ButtonList& butList);
	bool aboutMenu(RenderWindow& window);
	bool optionMenu(RenderWindow& window);

public:

	void create(RenderWindow& window, Font& FONT, GlobalData& data);

	bool mainMenu(RenderWindow& window, int& numberLevel);
	bool levelMenu(RenderWindow& window, int& numberLevel);

};


#endif MENU_H