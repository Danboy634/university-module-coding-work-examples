#ifndef _GAME_OBJECT_WITH_SPRITE_H
#define _GAME_OBJECT_WITH_SPRITE_H

#include "../../Engine/Renderer/Sprite.h"
#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Physics/BoxCollider2D.h"

class GameObjectWithSprite 
	: public GameObject, BoxCollider2D
{
public:
	GameObjectWithSprite();
	~GameObjectWithSprite();

	void Initialise();
	void Initialise(const char* filename, const int xPos, const int yPos, const int sizeX, const int sizeY);
	void Update();
	void GetPosition(int& x, int& y);

	virtual void OnCollision(Collider2D* pCollider2D);

private:
	Sprite m_Sprite;
};

#endif