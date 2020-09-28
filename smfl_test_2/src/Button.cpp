#include "Button.h"


using namespace sf;

Button::Button(const String& string, const Font& font, RenderWindow& WINDOW, bool back_show, int textSize, Color TextColor, Color BackColor)
{
	canPressed = true;
	viewable = true;
	m_backGroundDraw = back_show;
	m_indent = textSize;
	m_text.setFont(font);
	m_text.setFillColor(TextColor);
	m_text.setCharacterSize(WINDOW.getView().getSize().y / textSize); // scale for different resolution
	m_text.setString(string);
	m_backGround.setFillColor(BackColor);
	m_backGround.setSize(Vector2f(m_text.getGlobalBounds().width + m_indent * 2, m_text.getGlobalBounds().height + m_indent * 2));
}

void Button::update(float X, float Y)
{
	m_text.setPosition(X + m_indent, Y - m_indent);
	m_backGround.setPosition(X, Y);
}

void Button::update(Vector2f POS)
{
	m_text.setPosition(POS.x + m_indent, POS.y - m_indent);
	m_backGround.setPosition(POS.x, POS.y);
}

void Button::draw(RenderWindow& window)
{
	if (viewable) 
	{
		if (m_backGroundDraw) window.draw(m_backGround);
		window.draw(m_text);
	}
}

/*ButtonList::ButtonList(const Font& font, RenderWindow& WINDOW, std::vector<std::string> names, bool back_show, int textSize)
{
	m_lineIndent = WINDOW.getView().getSize().y / textSize;
	for (std::vector<std::string>::iterator name = names.begin(); name != names.end(); name++)
	{
		buttons.push_back(new Button(*name, font, WINDOW, back_show, textSize));
	}
	m_backGround.setFillColor(Color::Black);
}*/

void ButtonList::create(const Font& font, RenderWindow& WINDOW, std::vector<std::string> names, bool back_show, int textSize)
{
	m_lineIndent = WINDOW.getView().getSize().y / textSize;
	for (std::vector<std::string>::iterator name = names.begin(); name != names.end(); name++)
	{
		buttons.push_back(new Button(*name, font, WINDOW, back_show, textSize));
	}
	m_backGround.setFillColor(Color::Black);
}

void ButtonList::update()
{
	for (int i = 0; i<buttons.size();++i)
	{
		buttons[i]->update(butPos[i]);
	}
}

void ButtonList::composeYcenterXtop(RenderWindow& WINDOW)
{
	butPos.clear();
	while (butPos.size() != buttons.size()) butPos.push_back(Vector2f(0.f, 0.f));
	float offset = 1;
	float rectSizeY = 5.f;
	float rectSizeX = 0.f;
	for (std::vector<Button*>::iterator but = buttons.begin(); but != buttons.end(); but++)
	{
		if ((*but)->viewable)
		{
			butPos.at(std::distance(buttons.begin(), but)).x = WINDOW.getView().getSize().x / 2 - (*but)->getSize().x / 2;
			butPos.at(std::distance(buttons.begin(), but)).y = ((*but)->getSize().y + 5) * offset;
			offset++;
			if (rectSizeX <= (*but)->getSize().x)
			{
				rectSizeX = (*but)->getSize().x;
				maxButtonSizeId_X = std::distance(buttons.begin(), but);
			}
			rectSizeY += (*but)->getSize().y + 5;
		}
	}
	m_backGround.setSize(Vector2f(rectSizeX + 10, rectSizeY));
	m_backGround.setPosition(Vector2f(butPos[maxButtonSizeId_X].x - 5, butPos[0].y - m_lineIndent));
	update();
}

void ButtonList::composeYcenterXCenter(RenderWindow& WINDOW)
{
}

void ButtonList::draw(RenderWindow& window)
{
	if (m_viewable) 
	{
		window.draw(m_backGround);
		for (std::vector<Button*>::iterator but = buttons.begin(); but != buttons.end(); but++)
		{
			(*but)->draw(window);
		}
	}
	
}

void ButtonList::setTextFillColor(int ID, Color COLOR)
{
	if (checkID(ID)) buttons[ID]->setTextFillColor(COLOR);
}

void ButtonList::setViewable(int ID, bool viewable)
{
	{ if (checkID(ID)) buttons[ID]->viewable = viewable; }
}

void ButtonList::setPressable(int ID, bool pressable)
{
	if (checkID(ID)) buttons[ID]->canPressed = pressable;
}

void ButtonList::setPressable(bool pressable)
{
	for (std::vector<Button*>::iterator but = buttons.begin(); but != buttons.end(); but++)
	{
		(*but)->canPressed = pressable;
	}
}

bool ButtonList::getPressable(int ID, bool pressable)
{
	if (checkID(ID)) return buttons[ID]->canPressed;
	return false;
}

void ButtonList::checkMouseIntersects(int& ID, RenderWindow &window, Color TRUEcolor, Color FALSEcolor)
{
	for (std::vector<Button*>::iterator but = buttons.begin(); but != buttons.end(); but++)
	{
		if (((*but)->canPressed) && (IntRect((*but)->getRect()).contains(Mouse::getPosition(window))))
		{
			(*but)->setTextFillColor(TRUEcolor);
			ID = std::distance(buttons.begin(), but);
		}
		else (*but)->setTextFillColor(FALSEcolor);
	}
}



bool ButtonList::checkID(int ID)
{
	if ((ID > 0) && (ID < buttons.size())) return true;
	return false;
}
