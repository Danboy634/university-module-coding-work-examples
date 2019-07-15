#include "EndScreenState.h"

EndScreenState::EndScreenState()
{
}

EndScreenState::~EndScreenState()
{
}

void EndScreenState::Initialise(int playerScore)
{
	// Sets the score to the players score 
	m_Score = playerScore;
}

void EndScreenState::Initialise()
{
	// Gets camera position 
	m_Camera = new Camera();
	m_Camera->RemoveCamera();
	m_GameObjects.push_back(m_Camera);


	// Sets the mouse cusor to appear on the end screen

	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
	sf::RenderWindow* pWindow = pWindowManager->GetWindow();
	pWindow->setMouseCursorVisible(true);

	// Displays the background sprite and all text objects
	LevelEndScreen* pLevelEndScreen = new LevelEndScreen; 
	pLevelEndScreen->InitialiseBackgroundSprite("sprites/bg_end.png", 0, 0, 1024, 768);
	pLevelEndScreen->Initialise(m_Score);
	m_GameObjects.push_back(pLevelEndScreen);

	//Adds music to the screen
	AudioManager* pAudioManager = C_SysContext::Get<AudioManager>();
	pAudioManager->RemoveAllAudioObjects();
	pAudioManager->PlaySoundFX("sounds/sfx_coin1.wav");
	pAudioManager->PlayMusic("sounds/sound17.wav");
	pAudioManager->Update();
}

void EndScreenState::Update()
{
	GameState::Update();
}

GameObject * EndScreenState::GetPlayer()
{
	return nullptr;
}
