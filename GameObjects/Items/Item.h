#ifndef  ITEM_H
#define	 ITEM_H

#include "../../../Engine/Physics/BoxCollider2D.h"
#include "../../../Engine/Core/GameObject.h"
#include "../../../Engine/Renderer/Sprite.h"
#include "../../../Game/GameObjects/Player.h"
#include "../../../Game/Weapons/WeaponBase.h"
#include "../../../Engine/Renderer/RenderManager.h"


class Item :
	public GameObject, public BoxCollider2D
{
public:
	Item();
	virtual ~Item();
	virtual void Initialise(const int spriteID, const char* spriteSheetFileName, const char* animationName, const int fps, bool loop, int posX, int posY, int sizeX, int sizeY);
	virtual void Update(int activePickup);
	virtual void GetPosition(int& x, int& y);
	void SetPosition(int posX, int posY);
	//void SetPickup(char pickup);

	virtual void OnCollision(Collider2D* pCollider2D);

protected:
	int smallHealValue;
	int ammoRefillValue;

	bool m_itemCollected;

	char m_activePickup;

	WeaponBase* m_pWeapon;
	AnimatedSprite m_AnimatedSprite;

};


#endif // ! ITEM_H


