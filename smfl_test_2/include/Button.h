#ifndef BUTTON_H
#define BUTTON_H
#include "SFML/Graphics.hpp";

using namespace sf;

class Button: public Text
{
private:
	Vector2f m_size;
public:
	bool canPressed;
	bool viewable;


	Button(const String& string, const Font& font, unsigned int characterSize = 30)
		: Text(string, font, characterSize)
	{
		canPressed = true;
		viewable = true;
	}
	Vector2f getSize() 
	{ 
		m_size.x = getGlobalBounds().width; 
		m_size.y = getGlobalBounds().height; 
		return m_size; 
	}
};
#endif BUTTON_H