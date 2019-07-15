#include "GameStateTest.h"
#include "SFML/Window.hpp"
#include <random>

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../GameData/SpritesheetDef.h"
#include "../GameData/GameDataManager.h"
#include "../GameObjects/TileMap.h"
#include "../GameObjects/EnemyFactory.h"
#include "../GameObjects/EnemyFactoryImplementation.h"
#include "../GameObjects/EnemyBoss.h"

GameStateTest::GameStateTest()
{
	m_playerPositionX = 0;
	m_playerPositionY = 0;
	m_enemyPositionX = 0;
	m_enemyPositionY = 0;

	m_AmmoUIOffsetX = 435;
	m_AmmoUIOffsetY = 250;
	m_WepUIOffsetX = 380;
	m_WepUIOffsetY = 220;
	m_ScoreUIOffsetX = 500;
	m_ScoreUIOffsetY = -350;
	m_HealthUIOffsetX = -500;
	m_HealthUIOffsetY = -350;
}

GameStateTest::~GameStateTest()
{
	SAFE_DELETE_PTR(m_pPlayer);
	for (std::vector<EnemyBase*>::iterator it = m_pEnemiesList.begin(); it != m_pEnemiesList.end(); it++)
	{
		SAFE_DELETE_PTR(*it);
	}
	SAFE_DELETE_PTR(m_pBoss);
	SAFE_DELETE_PTR(m_HUD);
	SAFE_DELETE_PTR(m_pCamera);
	SAFE_DELETE_PTR(m_pWeapon);
	SAFE_DELETE_PTR(pbackgroundlevel);
	SAFE_DELETE_PTR(m_Crosshair);
}

void GameStateTest::Initialise()
{	
	m_currentLevel = E_LEVEL_ONE;

	// Loads background level

	BackgroundLevel* pbackgroundlevel = new BackgroundLevel;
	pbackgroundlevel->InitialiseLevelTwo("backgrounds/bg_ship_background.png", -100, -100, 50, 50);
	m_GameObjects.push_back(pbackgroundlevel);

	// Loads first tile map layer

	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSpritesheetDef = pGameDataManager->GetSpritesheetDef("backgrounds/bg_ship.xml");
	TileMap* pTileMap = new TileMap();
	pTileMap->LoadFromFileShipMap(pSpritesheetDef);
	m_GameObjects.push_back(pTileMap);

	// Loads second tile map layer

	TileMap* pTileMap1 = new TileMap();
	pTileMap1->Initialise();
	pTileMap1->LoadFromFileShipMap2(pSpritesheetDef);
	m_GameObjects.push_back(pTileMap1);
	
	// Load the items

	ItemFactory* m_ItemFactory = new ItemFactoryImplementation();


	for (int i = 0; i < 5; i++)
	{
		Item* smallHealth = m_ItemFactory->MakeItem(E_healthPickup);

		if (i == 0)
		{
			smallHealth->Initialise(1, "sprites/environment/spr_health_pickup.xml", "spr_pickup_health", 10, false, 10160, 1850, 1, 1);
			smallHealth->SetPosition(5140, 3636);
		}
		else if (i == 1)
		{
			smallHealth->Initialise(1, "sprites/environment/spr_health_pickup.xml", "spr_pickup_health", 10, false, 10320, 1850, 1, 1);

			smallHealth->SetPosition(6807, 134);
		}
		else if (i == 2)
		{
			smallHealth->Initialise(1, "sprites/environment/spr_health_pickup.xml", "spr_pickup_health", 10, false, 190, 2180, 1, 1);

			smallHealth->SetPosition(8133, 385);
		}
		else if (i == 3)
		{
			smallHealth->Initialise(1, "sprites/environment/spr_health_pickup.xml", "spr_pickup_health", 10, false, 10320, 1850, 1, 1);

			smallHealth->SetPosition(8512, 3705);
		}
		else if (i == 4)
		{
			smallHealth->Initialise(1, "sprites/environment/spr_health_pickup.xml", "spr_pickup_health", 10, false, 10320, 1850, 1, 1);

			smallHealth->SetPosition(10180, 1835);
		}

		smallHealth->Update(E_healthPickup);
		m_GameObjects.push_back(smallHealth);
	}
	for (int i = 0; i < 3; i++)
	{
		Item* smallAmmo = m_ItemFactory->MakeItem(E_ammoPickup);

		if (i == 0)
		{
			smallAmmo->Initialise(0, "sprites/environment/AmmoPickup.xml", "spr_pickup_light", 10, false, 9800, 1300, 2, 2);
			smallAmmo->SetPosition(1856, 3775);
		}
		else if (i == 1)
		{
			smallAmmo->Initialise(0, "sprites/environment/AmmoPickup.xml", "spr_pickup_light", 10, false, 9800, 1300, 2, 2);
			smallAmmo->SetPosition(5880, 2978);
		}
		else if (i == 2)
		{
			smallAmmo->Initialise(0, "sprites/environment/AmmoPickup.xml", "spr_pickup_light", 10, false, 9800, 1300, 2, 2);
			smallAmmo->SetPosition(10564, 1355);
		}

		smallAmmo->Update(E_healthPickup);
		m_GameObjects.push_back(smallAmmo);
	}

	// Loads the enemies

	EnemyFactory* m_EnemyFactory = new EnemyFactoryImplementation();

	//zone 1 enemies
	//Turtle Enemies
	for (int i = 0; i < 15; i++)
	{
		EnemyBase* enemyTurtle = m_EnemyFactory->MakeEnemy(E_ENEMY_TURTLE_1);
		enemyTurtle->Initialise();
		m_pEnemiesList.push_back(enemyTurtle);
	}

	//Duck 1 Enemies
	for (int i = 0; i < 7; i++)
	{
		EnemyBase* enemyDuck = m_EnemyFactory->MakeEnemy(E_ENEMY_DUCK_1);
		enemyDuck->Initialise();
		m_pEnemiesList.push_back(enemyDuck);
	}

	//Duck 2 Enemies
	for (int i = 0; i < 8; i++)
	{
		EnemyBase* enemyDuck = m_EnemyFactory->MakeEnemy(E_ENEMY_DUCK_2);
		enemyDuck->Initialise();
		m_pEnemiesList.push_back(enemyDuck);
	}

	//Ass Enemies
	for (int i = 0; i < 15; i++)
	{
		EnemyBase* enemyAss = m_EnemyFactory->MakeEnemy(E_ENEMY_ASS);
		enemyAss->Initialise();
		m_pEnemiesList.push_back(enemyAss);
	}

	//WormTurtle Enemies
	for (int i = 0; i < 15; i++)
	{
		EnemyBase* wormTurtle = m_EnemyFactory->MakeEnemy(E_ENEMY_TURTLE_WORM);
		wormTurtle->Initialise();
		m_pEnemiesList.push_back(wormTurtle);
	}

	//add all the enemy objects to the game world list of game objects
	for (std::vector<EnemyBase*>::iterator it = m_pEnemiesList.begin(); it != m_pEnemiesList.end(); it++)
	{
		m_GameObjects.push_back((*it));
	}

	//Boss Enemy
	EnemyBase* bossEnemy = m_EnemyFactory->MakeEnemy(E_ENEMY_BOSS);
	bossEnemy->Initialise();
	m_pBoss = (EnemyBoss*)bossEnemy;
	m_pBoss->SetBossStats(12000, 1575, 1800, 20, 5, 1500.f, 20);
	m_GameObjects.push_back(m_pBoss);

	// Load the HUD

	// Load the player

	m_pPlayer = new Player();
	m_pPlayer->Initialise(10, 300, 2000);
	m_GameObjects.push_back(m_pPlayer);

	m_HUD = new HUD();
	m_HUD->Initialise(1, "fonts/Grand9K Pixel_0.TTF");
	m_HUD->SetPosition(m_AmmoUIOffsetX, m_AmmoUIOffsetY, m_WepUIOffsetX, m_WepUIOffsetY, m_ScoreUIOffsetX, m_ScoreUIOffsetY, m_HealthUIOffsetX, m_HealthUIOffsetY);
	m_GameObjects.push_back(m_HUD);

	// Load the camera

	m_pCamera = new Camera();
	m_pCamera->Initialise();
	m_GameObjects.push_back(m_pCamera);

	// Set the window cursor to invisible

	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
	sf::RenderWindow* pWindow = pWindowManager->GetWindow();
	pWindow->setMouseCursorVisible(false);

	// Add in the crosshair cursor

	m_Crosshair = new WeaponCrosshair();
	m_Crosshair->Initialise("sprites/ui/spr_crosshair/spr_crosshair_1.png");
	m_GameObjects.push_back(m_Crosshair);

	// Add in the audio

	AudioManager* pAudioManager = C_SysContext::Get<AudioManager>();
	pAudioManager->RemoveAllAudioObjects();
	pAudioManager->PlayMusic("sounds/bgm_boss.wav");
	pAudioManager->Update();
	
}

void GameStateTest::Update()
{
	AudioManager* pAudioManager = C_SysContext::Get<AudioManager>();

	if (m_pBoss->IsBossDead() && m_pBoss->AnimationFinished())
	{
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		LevelOne* pLevelOne = new LevelOne;

		int score = m_pPlayer->getCurrentScore();
		//bonus score for the amount of health player has left
		score += (int)m_pPlayer->getCurrentHealth() / 10;
		//bonus score for beating the boss
		score += 200;
		pLevelOne->Initialise(score);
		pGameStateManager->QueueGameState(pLevelOne);
	}
	else if (m_pPlayer->GameOver())
	{
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		DeathScreenState* pDeathScreenState = new DeathScreenState;
		pGameStateManager->QueueGameState(pDeathScreenState);
	}

	GameState::Update();

//----Camera----
	m_pPlayer->GetPosition(m_playerPositionX, m_playerPositionY);

	if (m_playerPositionX <= 512)
	{
		camPosX = 512 - m_playerPositionX;
		m_pCamera->Update(m_playerPositionX + camPosX, m_playerPositionY);
	}
	else
	{
		m_pCamera->Update(m_playerPositionX, m_playerPositionY);
	}

//----UI----

	int m_HUDAmmunition = m_pPlayer->getWeaponAmmo();
	int m_HUDTotalAmmo = m_pPlayer->getAmmoInBag();
	int m_HUDReloading = m_pPlayer->getClipMax();
	int m_HUDScore = m_pPlayer->getCurrentScore();
	int m_HUDHealth = m_pPlayer->getCurrentHealth();
	
	m_HUD->setReloadSpritePosition(m_playerPositionX, m_playerPositionY);

	m_HUD->Update(m_HUDAmmunition, m_HUDTotalAmmo, m_HUDReloading, m_HUDScore, m_HUDHealth);

//----Menu/Level/Pause----

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		GameStateMenu* pGameStateMenu = new GameStateMenu;
		pGameStateManager->QueueGameState(pGameStateMenu);
	}
}

GameObject* GameStateTest::GetPlayer()
{
	return m_pPlayer;
}