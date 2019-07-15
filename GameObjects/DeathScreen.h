#ifndef _DEATH_SCREEN_H
#define _DEATH_SCREEN_H

#include "../../Engine/Core/GameObject.h"
#include "../../Engine/UI/Text.h"
#include "../../Engine/Renderer/Sprite.h"
#include "../../Engine//Physics/BoxCollider2D.h"
#include "../../Game/Game.h"
#include <SFML\Graphics.hpp>
#include "../../Engine/Renderer/AnimatedSprite.h"




class DeathScreen : public GameObject

{
public:

	DeathScreen();

	~DeathScreen();

	virtual void Update();

	virtual void Initialise();

	virtual void InitialiseBackgroundSprite(const char* filename, const int x, const int y, const int sizeX, const int sizeY);

	//void InitialiseText(const char * filename, const char * text, int textSize, sf::Color textColour, const int x, const int y, sf::Color Outlinecolour, const int OutlineThickness);

	virtual void GetPosition(int& x, int& y);

	virtual void OnCollision(Collider2D* pCollider2D);


private:

	Text GameOver_Text, 
		Retry_Text, 
		Yes_Text, 
		No_Text;

	Sprite m_Sprite,
		Small_Button,
		Small_Button2;

	sf::Vector2i mouseposition;

	AudioManager* pAudioManager;


};
#endif