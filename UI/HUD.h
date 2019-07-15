#ifndef _HUD_H
#define _HUD_H

#include "../GameObjects/Camera.h"
#include "../GameObjects/TileMap.h"
#include "../Weapons/BlitzWeapon.h"
#include "../../Engine/UI/Text.h"
#include "../../Engine/Core/GameObject.h"
#include "../../Game/Weapons/WeaponBase.h"
#include "../../Game/GameObjects/Player.h"
#include "../../Engine/Renderer/Sprite.h"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../GameData/GameDataManager.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/Renderer/RenderManager.h"


class HUD :
	public GameObject
{
public:
	HUD();
	~HUD();

	virtual void Initialise();
	virtual void Initialise(int fps, const char* font);
	virtual void Update();
	virtual void Update(int ammoValue, int totalAmmo, int clipValue, int scoreValue, int healthValue);
	virtual void GetPosition(int& x, int& y);
	void SetPosition(int AmmoX, int AmmoY, int WepX, int WepY, int ScoreX, int ScoreY, int HealthX, int HealthY);
	void setReloadSpritePosition(int playerPositionX, int playerPositionY);
private:

	//bool reloading;
	//bool fullyReloaded;

	//int m_Ammunition;

	int m_weaponSpriteIndex;

	WeaponBase* WeaponPtr;

	GameStateManager* P_currGameStateManager = C_SysContext::Get<GameStateManager>(); 
	GameState* p_currGameState = P_currGameStateManager->GetCurrentGameState();
	Player* PlayerPtr = (Player*)p_currGameState->GetPlayer(); //This gets the exact player

	Text m_Ammo;
	Text m_Reload;
	Text m_Score;
	Text m_Health;

	AnimatedSprite m_WeaponSprite;
	AnimatedSprite m_ReloadSprite;

	bool isReloading;

	enum E_health
	{
		E_Health_Empty,
		E_Health_Half,
		E_Health_Full,
		E_Health_Max
	};
};

#endif