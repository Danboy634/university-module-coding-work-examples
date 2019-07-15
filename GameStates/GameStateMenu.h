#ifndef _GAME_STATE_MENU_H
#define _GAME_STATE_MENU_H

#include <SFML\Graphics.hpp>
#include "../../Engine/System/GameState/GameState.h"
#include "../GameObjects/TextGameObject.h"
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


class GameStateMenu : 
	public GameState
{

public:
	GameStateMenu();
	virtual	~GameStateMenu();

	void Initialise();
	void Update();

	GameObject* GetPlayer();

private:
	Player* PlayerPtr;

};

#endif