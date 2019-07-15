#ifndef _TEXT_GAME_OBJECT_H
#define _TEXT_GAME_OBJECT_H

#include "../../Engine/UI/Text.h"
#include "../../Engine/Core/GameObject.h"

class TextGameObject
	: public GameObject
{
public:
	TextGameObject();
	~TextGameObject();

	void Initialise();
	void Initialise(const char* font, const char* text, int textSize, sf::Color textColour, const int x, const int y, sf::Color Outlinecolour, float OutlineThickness);
	void Update();
	void GetPosition(int& x, int& y);

private:
	Text m_Text;
};

#endif