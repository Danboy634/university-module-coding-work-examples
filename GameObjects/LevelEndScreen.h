#ifndef _LEVEL_END_SCREEN_H
#define _LEVEL_END_SCREEN_H

#include "../../Engine/Core/GameObject.h"
#include "../../Engine/UI/Text.h"
#include "../../Engine/Renderer/Sprite.h"
#include "../../Engine//Physics/BoxCollider2D.h"
#include "../../Game/Game.h"
#include <SFML\Graphics.hpp>
#include "../../Engine/Renderer/AnimatedSprite.h"



class LevelEndScreen : public GameObject
{
public:

	LevelEndScreen();

	~LevelEndScreen();

	virtual void Update();
	virtual void Initialise();
	void Initialise(int playerScore);
	virtual void InitialiseBackgroundSprite(const char* filename, const int x, const int y, const int sizeX, const int sizeY);

	virtual void GetPosition(int& x, int& y);
	virtual void OnCollision(Collider2D* pCollider2D);

private:

	Text Victory_Text, 
		Score_Text, 
		Return_Text;

	Sprite m_Sprite,
			Button_Sprite;

	sf::Vector2i mouseposition;

	AudioManager* pAudioManager;


};
#endif