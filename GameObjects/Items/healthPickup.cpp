#include "healthPickup.h"

healthPickup::healthPickup()
{
}


healthPickup::~healthPickup()
{
}

void healthPickup::Initialise()
{
}

void healthPickup::Initialise(const int spriteID, const char* spriteSheetFileName, const char* animationName, const int fps, bool loop, int posX, int posY, int sizeX, int sizeY)
{
	Item::Initialise(spriteID, spriteSheetFileName, animationName, fps, loop, posX, posY, sizeX, sizeY);
}

void healthPickup::Update()
{
	Item::Update(1);
}

void healthPickup::GetPosition(int & x, int & y)
{
	x = (int)m_smallHealth.getPosition().x;
	y = (int)m_smallHealth.getPosition().y;
}

void healthPickup::OnCollision(Collider2D* pCollider2D)
{
	if (pCollider2D->GetCollisionType() == E_Collider_Player)
	{
		Item::OnCollision(pCollider2D);
	}
}


