#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "GlobalData.h"
#include "Button.h"
#include <iostream>
#include <sstream>
#include <algorithm> 
using namespace sf; 


class Menu 
{
private:
	View m_menuView;
	int m_menuNum;
	Text m_text;
	ButtonList about, mainBut, lvl, levelChange; 
	std::map<std::string, int> optN;
	std::map < std::string, ButtonList> option;
	std::string m_progVer, m_mailInfo;
	void draw(RenderWindow& window, ButtonList& butList);
	void update(RenderWindow& window, ButtonList& butList);
	bool aboutMenu(RenderWindow& window);
	bool optionMenu(RenderWindow& window, GlobalData& data);
	bool levelMenu(RenderWindow& window, GlobalData& data);
	void composeAll(RenderWindow& window);
	Sound m_intersectSound;
public:

	void create(RenderWindow& window, Font& FONT, GlobalData& data);
	void setSound(Sound& SOUND) { m_intersectSound = SOUND; }
	bool mainMenu(RenderWindow& window, GlobalData& data);
	bool levelChangeMenu(RenderWindow& window, GlobalData& data);

};


#endif MENU_H