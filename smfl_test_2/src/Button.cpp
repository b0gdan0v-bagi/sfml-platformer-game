#include "Button.h"


using namespace sf;

Button::Button(const String& string, const Font& font, RenderWindow& WINDOW, bool back_show, int textSize, Color TextColor, Color BackColor)
{
	canPressed = true;
	viewable = true;
	//m_backGroundDraw = back_show;
	m_backGroundDraw = false;
	m_indent = textSize;
	m_charSize = textSize;
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

void Button::updateCharSize(RenderWindow& window)
{
	m_indent = m_charSize;
	m_text.setCharacterSize(window.getSize().y / m_charSize);
	m_backGround.setSize(Vector2f(m_text.getGlobalBounds().width + m_indent * 2, m_text.getGlobalBounds().height + m_indent * 2));
}

void Button::draw(RenderWindow& window)
{
	if (viewable) 
	{
		if (m_backGroundDraw) window.draw(m_backGround);
		//if (!canPressed) m_text.setFillColor(Color::Magenta);
		window.draw(m_text);
	}
}

void Button::draw(RenderWindow& window, View& VIEW)
{
	if (viewable)
	{
		window.setView(VIEW);
		if (m_backGroundDraw) window.draw(m_backGround);
		//if (!canPressed) m_text.setFillColor(Color::Magenta);
		window.draw(m_text);
	}
}

void ButtonList::create(const Font& font, RenderWindow& WINDOW, std::vector<std::string> names, bool back_show, int textSize)
{
	m_textSize = textSize;
	m_backGroundShow = back_show;
	for (std::vector<std::string>::iterator name = names.begin(); name != names.end(); name++)
	{
		buttons.push_back(new Button(*name, font, WINDOW, false, textSize));
	}
	m_backGround.setFillColor(Color::Black);
}

void ButtonList::update()
{
	for (int i = 0; i<buttons.size();++i) buttons[i]->update(butPos[i]);
}

void ButtonList::updateCharSize(RenderWindow& window)
{
	for (int i = 0; i < buttons.size(); ++i) buttons[i]->updateCharSize(window);
}

void ButtonList::composeY(RenderWindow& WINDOW, float X, float Y, int format)
{
	butPos.clear();
	float xCord = (1+X) * WINDOW.getView().getCenter().x;
	float yCord = (1+Y) * WINDOW.getView().getCenter().y;
	float offset = m_lineIndent.y;
	float rectSizeX = 0.f;
	for (std::vector<Button*>::iterator but = buttons.begin(); but != buttons.end(); but++)
	{
		if ((*but)->viewable)
		{
			
			butPos.push_back(Vector2f(xCord - format * (*but)->getSizeText().x / 2, yCord + offset));
			offset += (*but)->getSize().y + m_lineIndent.y;
			if (rectSizeX <= (*but)->getSizeText().x)
			{
				rectSizeX = (*but)->getSizeText().x;
				maxButtonSizeId_X = std::distance(buttons.begin(), but);
			}
		}
	}
	m_backGround.setSize(Vector2f(rectSizeX + m_lineIndent.x, offset + m_lineIndent.y));
	m_backGround.setPosition(Vector2f(butPos[0].x, butPos[0].y - m_lineIndent.y));
	update();
}

void ButtonList::composeX(RenderWindow& WINDOW, float X, float Y)
{
	butPos.clear();
	float xCord = (1 + X) * WINDOW.getView().getCenter().x;
	float yCord = (1 + Y) * WINDOW.getView().getCenter().y;
	float offset = m_lineIndent.x;
	float rectSizeY = m_lineIndent.y;
	for (std::vector<Button*>::iterator but = buttons.begin(); but != buttons.end(); but++)
	{
		if ((*but)->viewable)
		{	
			butPos.push_back(Vector2f(xCord + offset, yCord));
			offset += (*but)->getSizeText().x + m_lineIndent.x;
			rectSizeY = (*but)->getSize().y + m_lineIndent.y;
		}
	}
	m_backGround.setSize(Vector2f(offset + m_lineIndent.x, rectSizeY + m_lineIndent.y));
	m_backGround.setPosition(Vector2f(butPos[0].x - m_lineIndent.x * 2, butPos[0].y - m_lineIndent.y));
	update();
}

void ButtonList::draw(RenderWindow& window)
{
	if (m_viewable) 
	{
		if (m_backGroundShow) window.draw(m_backGround);
		for (std::vector<Button*>::iterator but = buttons.begin(); but != buttons.end(); but++)
		{
			(*but)->draw(window);
		}
	}
}

void ButtonList::draw(RenderWindow& window, View& VIEW)
{
	if (m_viewable)
	{
		window.setView(VIEW);
		if (m_backGroundShow) window.draw(m_backGround);
		for (std::vector<Button*>::iterator but = buttons.begin(); but != buttons.end(); but++)
		{
			(*but)->draw(window, VIEW);
		}
	}
}

void ButtonList::setTextFillColor(int ID, Color COLOR)
{
	if (checkID(ID)) buttons[ID]->setTextFillColor(COLOR);
}

void ButtonList::setViewable(int ID, bool VIEWABLE)
{
	if (checkID(ID)) buttons[ID]->viewable = VIEWABLE;
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

bool ButtonList::getPressable(int ID)
{
	if (checkID(ID)) return buttons[ID]->canPressed;
	return false;
}

void ButtonList::setBackgroundViewable(int ID, bool b)
{
	if (checkID(ID)) buttons[ID]->setBackgroundViewable(b);
}

bool ButtonList::getBackgroundViewable(int ID)
{
	if (checkID(ID)) return buttons[ID]->getBackgroundViewable();
	return false;
}

void ButtonList::switchBackgroundTo(int ID)
{
	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i]->setBackgroundViewable(false);
	}
	if (checkID(ID)) buttons[ID]->setBackgroundViewable(true);
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
	if ((ID >= 0) && (ID < buttons.size())) return true;
	return false;
}
