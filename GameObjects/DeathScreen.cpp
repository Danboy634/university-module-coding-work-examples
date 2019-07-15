#include "DeathScreen.h"

DeathScreen::DeathScreen()
{
}

DeathScreen::~DeathScreen()
{
}

void DeathScreen::Initialise()
{
	// Initialises the window view
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
	sf::RenderWindow* pWindow = pWindowManager->GetWindow();
	const sf::View view = pWindow->getView();

	// Initialises the mouse position relative to the window
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*pWindow);
	sf::Vector2f mouseWorldPos(mousePosition.x + (view.getCenter().x - (view.getSize().x * 0.5f)), mousePosition.y + (view.getCenter().y - (view.getSize().y * 0.5f)));

	// Initialises audio
	pAudioManager = C_SysContext::Get<AudioManager>();

	// Initialises the button sprites, then sets the position and the scale  
	Small_Button.Initialise("Sprites/spr_menu_button_small_0.png", 530, 270, 50, 30);
	Small_Button.setPosition(450, 267);
	Small_Button.setScale(0.6f, 0.9f);
	Small_Button2.Initialise("Sprites/spr_menu_button_small_0.png", 750, 270, 50, 30);
	Small_Button2.setPosition(680, 267);
	Small_Button2.setScale(0.6f, 0.9f);

	// Initialises Text
	GameOver_Text.InitialiseMenu("fonts/8-BIT WONDER.TTF", "GAME OVER", 40, sf::Color::Cyan, 465, 30, sf::Color::Black, 4);
	Retry_Text.InitialiseMenu("fonts/8-BIT WONDER.TTF", "Do you wish to retry", 35, sf::Color::Cyan, 340, 200, sf::Color::Black, 4);
	Yes_Text.InitialiseMenu("fonts/8-BIT WONDER.TTF", "YES", 35, sf::Color::Green, 479, 270, sf::Color::Black, 3);
	No_Text.InitialiseMenu("fonts/8-BIT WONDER.TTF", "NO", 35, sf::Color::Yellow, 726, 270, sf::Color::Black, 3);
}

void DeathScreen::InitialiseBackgroundSprite(const char* filename, const int x, const int y, const int sizeX, const int sizeY)
{
	// Initialises the death screen background sprite, and  sets the scale 

	m_Sprite.Initialise(filename, x, y, sizeX, sizeY);


	m_Sprite.setScale(1.0, 1.0);
}

void DeathScreen::Update()
{
	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	// Updates the window view
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
	sf::RenderWindow* pWindow = pWindowManager->GetWindow();
	const sf::View view = pWindow->getView();

	// Updates the mouse position relative to the window
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*pWindow);
	sf::Vector2f mouseWorldPos(mousePosition.x + (view.getCenter().x - (view.getSize().x * 0.5f)), mousePosition.y + (view.getCenter().y - (view.getSize().y * 0.5f)));

	// Gets the position of button image sprite
	if (((mousePosition.y > Small_Button.getGlobalBounds().top) && (mousePosition.y < (Small_Button.getGlobalBounds().top + Small_Button.getGlobalBounds().height))) && ((mousePosition.x > Small_Button.getGlobalBounds().left) && (mousePosition.x < (Small_Button.getGlobalBounds().left + Small_Button.getGlobalBounds().width))))
	{
		// When the mouse is in sprite bounds and clicked...
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // Clicking the mouse starts the game
		{
			pAudioManager->PlaySoundFX("sounds/sfx_coin1.wav"); // Play Sound effect
																				
			GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
			GameStateTest* pGameStateTest = new GameStateTest;
			pGameStateManager->QueueGameState(pGameStateTest);// Que GameStateTest

		}

	}

	// Gets the position of button image sprite
	if (((mousePosition.y > Small_Button2.getGlobalBounds().top) && (mousePosition.y < (Small_Button2.getGlobalBounds().top + Small_Button2.getGlobalBounds().height))) && ((mousePosition.x > Small_Button2.getGlobalBounds().left) && (mousePosition.x < (Small_Button2.getGlobalBounds().left + Small_Button2.getGlobalBounds().width))))
	{
		// When the mouse is in sprite bounds and clicked...
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // Clicking the mouse starts the game
		{
			pAudioManager->PlaySoundFX("sounds/sfx_coin1.wav"); // Play Sound effect
																	
			GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
			GameStateMenu* pGameStateMenu = new GameStateMenu;
			pGameStateManager->QueueGameState(pGameStateMenu); // Que GameStateMenu
		}
	}
}



void DeathScreen::GetPosition(int & x, int & y)
{


}

void DeathScreen::OnCollision(Collider2D * pCollider2D)
{
}