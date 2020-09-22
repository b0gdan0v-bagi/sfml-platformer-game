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
	std::vector<Text*> buttons;

public:
	RectangleShape testShape;
	void create(RenderWindow& window, Font& FONT);
	void update(RenderWindow& window);
	void composeButtons(std::vector<Text*> BUTTON);
	void draw(RenderWindow& window);
};

#endif INTERFACE_H
