#ifndef _MENU_H
#define _MENU_H

#include "../../Engine/Core/GameObject.h"
#include "../../Engine/UI/Text.h"
#include "../../Engine/Renderer/Sprite.h"
#include "../../Engine//Physics/BoxCollider2D.h"
#include "../../Game/Game.h"
#include <SFML\Graphics.hpp>

class Menu : public GameObject, public BoxCollider2D
{
public:
	Menu();
	virtual ~Menu();

	void InitialiseText(const char * filename, const char * text, int textSize, sf::Color textColour, const int x, const int y, sf::Color textOutlineColour, float textOutlineThickness);

	virtual void Update();

	virtual void Initialise();

	virtual void InitialiseSprite(const char* filename, const int x, const int y, const int sizeX, const int sizeY);

	virtual void GetPosition(int& x, int& y);

	virtual void OnCollision(Collider2D* pCollider2D);

	bool options = false;

private:

	enum E_MenuOption
	{
		E_StartGame_Initialise,
		E_StartGame_Update,
		E_Options_Initialise,
		E_Options_Update,
		E_Quit,
		E_Pause
	};

	E_MenuOption m_EMenuOption;
	
	Text StartGame_Text,
		Options_Text,
		QuitGame_Text,
		Options_Return_Text;
	
	Sprite m_Sprite,
		Background_Box_Image,
		Background_Box_Image_2,
		Background_Box_Image_3,
		Background_Box_Options,
		Background_Sprite_Image,
		Background_Sprite_Image2,
		background_Sprite_Image3;

	AnimatedSprite m_AnimatedSprite;
	sf::Vector2i mouseposition;

	AudioManager* pAudioManager;

};
#endif




