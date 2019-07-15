#include "DeathScreenState.h"


DeathScreenState::DeathScreenState()
{
}

DeathScreenState::~DeathScreenState()
{
}

void DeathScreenState::Initialise()
{
	// Gets camera position 
	m_Camera = new Camera();
	m_Camera->RemoveCamera();
	m_GameObjects.push_back(m_Camera);

	// Sets the mouse cusor to appear on the death screen
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
	sf::RenderWindow* pWindow = pWindowManager->GetWindow();
	pWindow->setMouseCursorVisible(true);

	// Loads in the background sprite and all text objects
	DeathScreen* pDeathScreen = new DeathScreen; 
	pDeathScreen->InitialiseBackgroundSprite("sprites/bg_pause.png", 0, 0, 1024, 768);
	pDeathScreen->Initialise();
	m_GameObjects.push_back(pDeathScreen);

	//Adds music to the screen
	AudioManager* pAudioManager = C_SysContext::Get<AudioManager>();
	pAudioManager->RemoveAllAudioObjects();
	pAudioManager->PlaySoundFX("sounds/sfx_player_death.wav");
	pAudioManager->PlayMusic("sounds/bgm_boss.wav");
	pAudioManager->Update();


}

void DeathScreenState::Update()
{
	GameState::Update();
}

GameObject * DeathScreenState::GetPlayer()
{
	return nullptr;
}
