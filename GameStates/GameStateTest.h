#ifndef _GAME_STATE_TEST_H
#define _GAME_STATE_TEST_H

#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../GameObjects/GameObjectWithSprite.h"
#include "../GameObjects/GameObjectWithAnimatedSprite.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Camera.h"
#include "../GameObjects/EnemyBase.h"
#include "../Game.h"
#include "../UI/HUD.h"
#include "../Weapons/WeaponBase.h"
#include "../GameObjects/WeaponCrosshair.h"
#include "../GameStates/GameStateMenu.h"
#include "../GameStates/LevelOne.h"
#include "../GameObjects/BackgroundLevel.h"
#include "../../Game/GameStates/EndScreenState.h"
#include "../../Game/GameStates/DeathScreenState.h"
#include"../GameObjects/Items/ItemFactory.h"
#include"../GameObjects/Items/ItemFactoryImplementation.h"
#include "../GameObjects/Items/healthPickup.h"

class GameStateTest :
	public GameState
{
public: 
	GameStateTest();
	virtual ~GameStateTest();

	void Update();
	void Initialise();
	GameObject* GetPlayer();

private:
	// --- Member variables/Pointers need to be written the same way...
	Player* m_pPlayer;
	std::vector<EnemyBase*> m_pEnemiesList;
	EnemyBoss* m_pBoss;
	HUD* m_HUD;
	Camera* m_pCamera;
	WeaponBase* m_pWeapon;


	BackgroundLevel* pbackgroundlevel;
	WeaponCrosshair* m_Crosshair;

	int m_playerPositionX;
	int m_playerPositionY;
	int m_enemyPositionX;
	int m_enemyPositionY;

	int m_AmmoUIOffsetX;
	int m_AmmoUIOffsetY;
	int m_WepUIOffsetX;
	int m_WepUIOffsetY;
	int m_ScoreUIOffsetX;
	int m_ScoreUIOffsetY;
	int m_HealthUIOffsetX;
	int m_HealthUIOffsetY;

	TileMap* m_pTileMap;

	int camPosX;
	
};

#endif