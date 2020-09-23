#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFML/Graphics.hpp>
#include "Button.h"

using namespace sf;

class GameInterface :public RectangleShape
{
private:
	Font m_font;
	float m_fontSize;
	Vector2f m_center, m_size; // for window.getView
	std::vector<Button*> m_buttons;
	bool m_active;
	int m_menuNum;
	RectangleShape m_Shape;
	//Text m_defeatText;
	bool m_defeatTextVisible;
	float m_indent;
public:
	
	void create(RenderWindow& window, Font& FONT);
	void update(RenderWindow& window, bool& EXIT);
	void composeButtons(std::vector<Button*> BUTTON);
	void draw(RenderWindow& window);
	void callInGameMenu() {m_active = true; }
	bool getActive() { return m_active; }
	void setDefeatTextVisible(bool VISIBLE) { m_defeatTextVisible = VISIBLE; }
};

#endif INTERFACE_H
