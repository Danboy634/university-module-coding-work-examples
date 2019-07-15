#ifndef  HEALTH_PICKUP_H
#define  HEALTH_PICKUP_H

#include "Item.h"

#include "../../../Engine/Renderer/Sprite.h"
#include "../../../Engine/Core/GameObject.h"
#include "../../../Engine/Physics/BoxCollider2D.h"
#include "../../../Engine/System/Context/SysContextProvider.h"
#include "../../../Engine/System/GameState/GameStateManager.h"
#include "../../../Engine/System/GameState/GameState.h"

class healthPickup :
	public Item
{
public:
	healthPickup();
	~healthPickup();

	void Initialise();
	void Initialise(const int spriteID, const char* spriteSheetFileName, const char* animationName, const int fps, bool loop, int posX, int posY, int sizeX, int sizeY);
	void Update();
	void GetPosition(int& x, int& y);


	virtual void OnCollision(Collider2D* pCollider2D);



private:
	AnimatedSprite m_smallHealth;
};

#endif // ! HEALTH_PICKUP_H

