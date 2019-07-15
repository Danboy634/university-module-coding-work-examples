#include "TextGameObject.h"

TextGameObject::TextGameObject()
{

}

TextGameObject::~TextGameObject()
{

}

void TextGameObject::Initialise()
{

}

void TextGameObject::Initialise(const char* font, const char* text, int textSize, sf::Color textColour, const int x, const int y, sf::Color Outlinecolour, float OutlineThickness)
{
	m_Text.InitialiseMenu(font, text, textSize, textColour, x, y, Outlinecolour, OutlineThickness);
}

void TextGameObject::Update()
{

}

void TextGameObject::GetPosition(int& x, int& y)
{
	x = (int)m_Text.GetText().getPosition().x;
	y = (int)m_Text.GetText().getPosition().y;
}