#ifndef  AMMO_PICKUP_H
#define  AMMO_PICKUP_H

#include "Item.h"

class ammoPickup :
	public Item
{
public:
	ammoPickup();
	~ammoPickup();

	void Initialise();
	void Initialise(const int spriteID, const char* spriteSheetFileName, const char* animationName, const int fps, bool loop, int posX, int posY, int sizeX, int sizeY);
	void Update();
	void GetPosition(int& x, int& y);

	virtual void OnCollision(Collider2D* pCollider2D);

private:
	AnimatedSprite m_smallAmmo;
};

#endif