#ifndef _END_SCREEN_STATE_H
#define _END_SCREEN_STATE_H

#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Drawable.hpp>
#include "../../Engine/System/GameState/GameState.h"
#include "../GameObjects/TextGameObject.h"
#include "../GameObjects/GameObjectWithSprite.h"
#include "../GameObjects/GameObjectWithSprite.h"
#include "../GameObjects/GameObjectWithAnimatedSprite.h"
#include "../GameData/GameDataManager.h"
#include "../GameObjects/Player.h"
#include "../Weapons/BlitzWeapon.h"
#include "../Weapons/WeaponBase.h"
#include "../GameObjects/TileMap.h"
#include "../GameObjects/Camera.h"
#include "../GameStates/GameStateTest.h"
#include "../GameObjects/Menu.h"
#include "../GameObjects/DynamicMenu.h"
#include "../GameObjects/LevelEndScreen.h"


class EndScreenState :
	public GameState
{
public:
	EndScreenState();
	virtual ~EndScreenState();

	void Initialise(int playerScore);

	void Initialise();
	void Update();

	GameObject* GetPlayer();

private:
	Camera* m_Camera;
	Player* pPlayer;

	int m_Score;

};

#endif