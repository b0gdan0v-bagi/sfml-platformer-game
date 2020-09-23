#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFML/Graphics.hpp>

using namespace sf;

class GameInterface :public RectangleShape
{
private:
	Font m_font;
	float m_fontSize;
	Vector2f m_center, m_size; // for window.getView
	std::vector<Text*> m_buttons;
	bool m_active;
	int m_menuNum;
	RectangleShape m_Shape;
public:
	
	void create(RenderWindow& window, Font& FONT);
	void update(RenderWindow& window);
	void composeButtons(std::vector<Text*> BUTTON);
	void draw(RenderWindow& window, bool& EXIT);
	void callInGameMenu();
	bool getActive() { return m_active; }
};

#endif INTERFACE_H
