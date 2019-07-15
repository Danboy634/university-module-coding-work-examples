#ifndef _LEVEL_ONE_H
#define _LEVEL_ONE_H

#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../GameObjects/TextGameObject.h"
#include "../GameObjects/GameObjectWithSprite.h"
#include "../GameObjects/GameObjectWithAnimatedSprite.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Camera.h"
#include "../GameObjects/EnemyBase.h"
#include "../GameObjects/EnemyBoss.h"
#include "../Game.h"
#include "../UI/HUD.h"
#include "../Weapons/WeaponBase.h"
#include "../GameObjects/WeaponCrosshair.h"
#include "../GameStates/GameStateMenu.h"
#include "../GameObjects/BackgroundLevel.h"
#include "../../Game/GameStates/EndScreenState.h"
#include "../../Game/GameStates/DeathScreenState.h"

class LevelOne :
	public GameState
{
public: 
	LevelOne();
	virtual ~LevelOne();

	virtual void Update();
	virtual void Initialise();
	virtual void Initialise(int playerScore);
	GameObject* GetPlayer();

private:
	Player* m_pPlayer;
	std::vector<EnemyBase*> m_pEnemiesList;
	EnemyBoss* m_pBoss;
	HUD* m_HUD;
	Camera* m_pCamera;
	WeaponBase* m_pWeapon;

	int m_PrevScore;

	WeaponCrosshair* m_Crosshair;
	BackgroundLevel* pbackgroundlevel;

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

	int camPosX;
};

#endif 
