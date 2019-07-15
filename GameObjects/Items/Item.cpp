#include "Item.h"

Item::Item()
{
	smallHealValue = 10;
	ammoRefillValue = 10;
	m_itemCollected = false;
}


Item::~Item()
{
	C_SysContext::Get<RenderManager>()->RemoveRenderObject(&m_AnimatedSprite);
}

void Item::Initialise(const int spriteID, const char* spriteSheetFileName, const char* animationName, const int fps, bool loop, int posX, int posY, int sizeX, int sizeY)
{
	//m_CollisionRect = m_Sprite.getGlobalBounds();
	//m_CollisionType = E_Collider_Object;
	//m_Sprite.Initialise(filename, xPos, yPos, sizeX, sizeY);

	GameDataManager* pGameDataManager = C_SysContext::Get <GameDataManager>();
	SpritesheetDef* pSpritesheetDef = pGameDataManager->GetSpritesheetDef(spriteSheetFileName);

	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(spriteID, pSpritesheetDef, animationName, fps, loop);
	m_AnimatedSprite.SetCurrentAnimation(spriteID);
	m_AnimatedSprite.setPosition((float)posX, (float)posY);
	m_AnimatedSprite.setScale((float)sizeX, (float)sizeY);
	m_AnimatedSprite.SetVisible(true);

	C_SysContext::Get<RenderManager>()->AddRenderObject(&m_AnimatedSprite);

	m_CollisionRect = m_AnimatedSprite.getGlobalBounds();
}

void Item::Update(int activePickup)
{
	GameStateManager* P_currGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* p_currGameState = P_currGameStateManager->GetCurrentGameState();
	Player* PlayerPtr = (Player*)p_currGameState->GetPlayer(); //This gets the exact player


	if (m_itemCollected)
	{
		m_AnimatedSprite.Animate();
		if (m_AnimatedSprite.AnimationFinished())
		{
			if (activePickup == 1)
			{
				PlayerPtr->GainHealth(100);
				p_currGameState->RemoveGameObject(this);
			}
			else if (activePickup == 0)
			{
				PlayerPtr->setAmmoInBag(15);
				p_currGameState->RemoveGameObject(this);
			}	
		}
	}

	m_CollisionRect = m_AnimatedSprite.getGlobalBounds();
}

void Item::SetPosition(int posX, int posY)
{
	m_AnimatedSprite.setPosition((float)posX, (float)posY);
}

//void Item::SetPickup(char pickup)
//{
//	m_activePickup = pickup;
//	return m_activePickup;
//}

void Item::GetPosition(int & x, int & y)
{
	x = (int)m_AnimatedSprite.getPosition().x;
	y = (int)m_AnimatedSprite.getPosition().y;
}

void Item::OnCollision(Collider2D* pCollider2D)
{
	m_itemCollected = true;
}
