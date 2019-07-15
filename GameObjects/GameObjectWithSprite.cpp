#include "GameObjectWithSprite.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"

GameObjectWithSprite::GameObjectWithSprite()
{
}

GameObjectWithSprite::~GameObjectWithSprite()
{
}

void GameObjectWithSprite::Initialise()
{
}

void GameObjectWithSprite::Initialise(const char* filename, const int xPos, const int yPos, const int sizeX, const int sizeY)
{
	m_Sprite.Initialise(filename, xPos, yPos, sizeX, sizeY);
	m_CollisionRect = m_Sprite.getGlobalBounds();
}

void GameObjectWithSprite::Update()
{
	m_Sprite.setPosition(400, 200);

	m_CollisionRect = m_Sprite.getGlobalBounds();
}

void GameObjectWithSprite::GetPosition(int& x, int& y)
{
	x = (int)m_Sprite.getPosition().x;
	y = (int)m_Sprite.getPosition().y;
}

void GameObjectWithSprite::OnCollision(Collider2D* pCollider2D)
{
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();

	pCurrentGameState->RemoveGameObject(this);
}
