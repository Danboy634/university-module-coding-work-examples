#include "ammoPickup.h"

ammoPickup::ammoPickup()
{
}

ammoPickup::~ammoPickup()
{
}

void ammoPickup::Initialise()
{
}

void ammoPickup::Initialise(const int spriteID, const char* spriteSheetFileName, const char* animationName, const int fps, bool loop, int posX, int posY, int sizeX, int sizeY)
{
	Item::Initialise(spriteID, spriteSheetFileName, animationName, fps, loop, posX, posY, sizeX, sizeY);
}

void ammoPickup::Update()
{
	Item::Update(0);
}

void ammoPickup::GetPosition(int & x, int & y)
{
	x = (int)m_smallAmmo.getPosition().x;
	y = (int)m_smallAmmo.getPosition().y;
}

void ammoPickup::OnCollision(Collider2D * pCollider2D)
{
	if (pCollider2D->GetCollisionType() == E_Collider_Player)
	{
		Item::OnCollision(pCollider2D);	
	}
}
