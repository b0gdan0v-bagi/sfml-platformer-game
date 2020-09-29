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
	Vector2f m_size;
public:

	bool canPressed;
	bool viewable;


	Button(const String& string, const Font& font, RenderWindow& WINDOW,
		bool back_show = false, int textSize = 25, Color TextColor = Color::White, Color BackColor = Color::Black);

	Vector2f getSize() { return m_backGround.getSize(); }
	void setTextFillColor(Color COLOR) { m_text.setFillColor(COLOR); }
	void update(float X, float Y);
	void update(Vector2f POS);
	//FloatRect getRect() { return FloatRect(m_backGround.getPosition(),m_backGround.getSize()); }
	FloatRect getRect() { return m_text.getGlobalBounds(); }
	void draw(RenderWindow& window);
};

class ButtonList
{
private:
	bool m_backGroundShow;
	float m_lineIndent;
	bool m_viewable;
	RectangleShape m_backGround;
	int maxButtonSizeId_X;
public:
	std::vector<Vector2f> butPos;
	std::vector<Button*> buttons;
	ButtonList();
	//ButtonList(const Font& font, RenderWindow& WINDOW, std::vector<std::string> names, bool back_show = false
	//	, int textSize = 25);
	
	void create(const Font& font, RenderWindow& WINDOW, std::vector<std::string> names, bool back_show = false
		, int textSize = 25);
	void update();
	void composeYcenterXtop(RenderWindow& WINDOW);
	void composeYcenterXCenter(RenderWindow& WINDOW);
	void composeY(RenderWindow& WINDOW, float X, float Y);
	void composeX(RenderWindow& WINDOW, float X, float Y);
	void draw(RenderWindow& window);
	void setTextFillColor(int ID, Color COLOR);
	void setViewable(bool viewable) { m_viewable = viewable; }
	void setViewable(int ID, bool viewable);
	void setPressable(int ID, bool pressable);
	void setPressable(bool pressable);
	bool getPressable(int ID, bool pressable);
	void checkMouseIntersects(int& ID,RenderWindow &window, Color TRUEcolor, Color FALSEcolor);
	bool checkID(int ID);
	void setLineIndent(float INDENT) { m_lineIndent = INDENT; }

	~ButtonList()
	{
		for (std::vector<Button*>::iterator but = buttons.begin(); but != buttons.end(); but++) delete* but;
		buttons.clear();
	}
};

#endif BUTTON_H