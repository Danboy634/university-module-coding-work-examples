#include "GameStateMenu.h"

GameStateMenu::GameStateMenu()
{
}

GameStateMenu::~GameStateMenu()
{
}

void GameStateMenu::Initialise()
{
	// Removes the camera
	Camera* m_Camera = new Camera();
	m_Camera->RemoveCamera();
	m_GameObjects.push_back(m_Camera);

	// Adds the menu	
	Menu* m_pMenu = new Menu();
	m_pMenu->Initialise();
	m_pMenu->Update();
	m_GameObjects.push_back(m_pMenu);
	
	// Adds the dynamic menu animation to menu
	DynamicMenu* pDynamicMenu = new DynamicMenu();
	pDynamicMenu->Initialise();
	pDynamicMenu->Update();
	m_GameObjects.push_back(pDynamicMenu);
	
	// Sets the cursor to visible
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
	sf::RenderWindow* pWindow = pWindowManager->GetWindow();
	pWindow->setMouseCursorVisible(true);

	// Removes all previous music and plays music
	AudioManager* pAudioManager = C_SysContext::Get<AudioManager>();
	pAudioManager->RemoveAllAudioObjects();
	pAudioManager->PlayMusic("sounds/sound17.wav");
	pAudioManager->Update();
}

void GameStateMenu::Update()
{

	GameState::Update(); // updates the gamestate with - UpdateGameObjects(), UpdateCollisions(), AddAndRemoveGameObjects(), AddAndRemoveColliders()

}

GameObject* GameStateMenu::GetPlayer()
{
	return NULL;
}