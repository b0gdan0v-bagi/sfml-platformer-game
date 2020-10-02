#ifndef BUTTON_H
#define BUTTON_H
#include "SFML/Graphics.hpp";
#include <iostream>

using namespace sf;

class Button
{
private:
	Text m_text; //message text
	RectangleShape m_backGround; // background 
	bool m_backGroundDraw;
	float m_indent;
	float m_charSize;
	Vector2f m_size;
public:

	bool canPressed;
	bool viewable;


	Button(const String& string, const Font& font, RenderWindow& WINDOW,
		bool back_show = false, int textSize = 25, Color TextColor = Color::White, Color BackColor = Color::Black);

	Vector2f getSize() { return m_backGround.getSize(); } //chancged to text
	Vector2f getSizeText() { return Vector2f(m_text.getGlobalBounds().width, m_text.getGlobalBounds().height); }
	void setTextFillColor(Color COLOR) { m_text.setFillColor(COLOR); }
	void setBackgroundViewable(bool b) { m_backGroundDraw = b; }
	bool getBackgroundViewable() { return m_backGroundDraw; }
	void update(float X, float Y);
	void update(Vector2f POS);
	void updateCharSize(RenderWindow& window);
	void setButtonString(std::string STRING_but) { 	m_text.setString(STRING_but); }
	//FloatRect getRect() { return FloatRect(m_backGround.getPosition(),m_backGround.getSize()); }
	FloatRect getRect() { return m_text.getGlobalBounds(); }
	void draw(RenderWindow& window);
	void draw(RenderWindow& window, View& VIEW);
};

class ButtonList
{
private:
	bool m_backGroundShow = { false };
	Vector2f m_lineIndent = { 50, 10 };
	float m_textSize = { 20 };
	bool m_viewable = { false };
	RectangleShape m_backGround;
	int maxButtonSizeId_X = { 0 };
public:
	std::vector<Vector2f> butPos;
	std::vector<Button*> buttons;
	
	ButtonList() {}
	ButtonList(const Font& font, RenderWindow& WINDOW, std::vector<std::string> names, bool back_show = false
		, int textSize = 25);
	void create(const Font& font, RenderWindow& WINDOW, std::vector<std::string> names, bool back_show = false
		, int textSize = 25);
	void update();
	void updateCharSize(RenderWindow& window);
	void composeY(RenderWindow& WINDOW, float X, float Y, int format = 1);
	void composeX(RenderWindow& WINDOW, float X, float Y);
	void draw(RenderWindow& window);
	void draw(RenderWindow& window, View& VIEW);
	void setTextFillColor(int ID, Color COLOR);
	void setViewable(bool viewable) { m_viewable = viewable; }
	void setViewable(int ID, bool viewable);
	void setPressable(int ID, bool pressable);
	void setPressable(bool pressable);
	bool getPressable(int ID);
	void setViewAndPressable(int ID, bool b) { setViewable(ID, b); setPressable(ID, b); }
	void setButtonString(int ID, std::string STRING);
	void setBackgroundViewable(int ID, bool b);
	bool getBackgroundViewable(int ID);
	void switchBackgroundTo(int ID);
	void switchBackgroundTo();
	void checkMouseIntersects(int& ID,RenderWindow &window, Color TRUEcolor, Color FALSEcolor);
	bool checkID(int ID);
	void setLineIndent(Vector2f INDENT) { m_lineIndent = INDENT; }

	~ButtonList()
	{
		for (std::vector<Button*>::iterator but = buttons.begin(); but != buttons.end(); but++) delete* but;
		buttons.clear();
	}
};

#endif BUTTON_H