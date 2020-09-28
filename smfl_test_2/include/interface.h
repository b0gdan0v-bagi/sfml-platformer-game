#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFML/Graphics.hpp>
#include "Button.h"

using namespace sf;

class GameInterface :public RectangleShape
{
private:
	Vector2f m_center, m_size; // for window.getView
	ButtonList buttList;
	bool m_active;
	int m_menuNum;
	bool m_defeatTextVisible;
	float m_indent;
public:
	
	void create(RenderWindow& window, Font& FONT);
	void update(RenderWindow& window, int& STATE);
	void draw(RenderWindow& window);
	void callInGameMenu() {m_active = true; }
	bool getActive() { return m_active; }
	void setDefeatTextVisible(bool VISIBLE) { m_defeatTextVisible = VISIBLE; }
};

#endif INTERFACE_H
