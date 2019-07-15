#include "GameObjectWithAnimatedSprite.h"
#include "../../Game/GameData/GameDataManager.h"

GameObjectWithAnimatedSprite::GameObjectWithAnimatedSprite()
{
}

GameObjectWithAnimatedSprite::~GameObjectWithAnimatedSprite()
{
}

void GameObjectWithAnimatedSprite::Initialise()
{
}

void GameObjectWithAnimatedSprite::Initialise(const int spriteID, const char* spriteSheetFileName, const char* animationName,const int fps, bool loop, int posX, int posY)
{
	GameDataManager* pGameDataManager = C_SysContext::Get <GameDataManager>();
	SpritesheetDef* pSpritesheetDef = pGameDataManager->GetSpritesheetDef(spriteSheetFileName);

	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(spriteID, pSpritesheetDef, animationName, fps, loop);
	m_AnimatedSprite.SetCurrentAnimation(spriteID);

	m_AnimatedSprite.setPosition((float)posX, (float)posY);
	m_AnimatedSprite.setScale(2.f, 2.f);
}

void GameObjectWithAnimatedSprite::Update()
{
}

void GameObjectWithAnimatedSprite::Update(int scaleX)
{
	m_AnimatedSprite.Animate();
	m_AnimatedSprite.move((float)scaleX * -1.f, -1.f);
}

void GameObjectWithAnimatedSprite::GetPosition(int& x, int& y)
{
	x = (int)m_AnimatedSprite.getPosition().x;
	y = (int)m_AnimatedSprite.getPosition().y;
}

bool GameObjectWithAnimatedSprite::AnimationFinished()
{
	if (m_AnimatedSprite.AnimationFinished())
	{
		return true;
	}
	else
	{
		return false;
	}
}
