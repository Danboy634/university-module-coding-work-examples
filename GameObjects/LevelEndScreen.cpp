#include "LevelEndScreen.h"

LevelEndScreen::LevelEndScreen()
{
}

LevelEndScreen::~LevelEndScreen()
{
}

void LevelEndScreen::Initialise()
{
}

void LevelEndScreen::Initialise(int playerScore)
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

	// Initialises the button sprite, then sets the position and the scale  
	Button_Sprite.Initialise("Sprites/spr_menu_buttonMain_1.png", 35, 80, 50, 50);
	Button_Sprite.setPosition(0, 600);
	Button_Sprite.setScale(0.75f, 0.9f);

	// Adds the score
	std::string m_score = "Score: " + std::to_string(playerScore);
	const char* score = m_score.c_str();

	// Initialises Text
	Victory_Text.InitialiseMenu("fonts/8-BIT WONDER.TTF", "Congratulations", 40, sf::Color::Blue, 380, 30, sf::Color::White, 5);
	Score_Text.InitialiseMenu("fonts/Grand9K Pixel_0.TTF", score, 38, sf::Color::Blue, 390, 130, sf::Color::White, 2);
	Return_Text.InitialiseMenu("fonts/Grand9K Pixel_0.TTF", "Return to menu", 35, sf::Color::Blue, 9, 603, sf::Color::White, 3);
}

void LevelEndScreen::InitialiseBackgroundSprite(const char* filename, const int x, const int y, const int sizeX, const int sizeY)
{
	// Initialises the level end screen background sprite, and  sets the scale 

	m_Sprite.Initialise(filename, x, y, sizeX, sizeY);

	m_Sprite.setScale(0.75, 0.75);
}


void LevelEndScreen::Update()
{
	// Gets the window size 
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
	sf::RenderWindow* pWindow = pWindowManager->GetWindow();
	const sf::View view = pWindow->getView();

	sf::Vector2i mousePosition = sf::Mouse::getPosition(*pWindow);
	sf::Vector2f mouseWorldPos(mousePosition.x + (view.getCenter().x - (view.getSize().x * 0.5f)), mousePosition.y + (view.getCenter().y - (view.getSize().y * 0.5f)));

	// Gets the position of button image sprite
	if (((mousePosition.y > Button_Sprite.getGlobalBounds().top) && (mousePosition.y < (Button_Sprite.getGlobalBounds().top + Button_Sprite.getGlobalBounds().height))) && ((mousePosition.x > Button_Sprite.getGlobalBounds().left) && (mousePosition.x < (Button_Sprite.getGlobalBounds().left + Button_Sprite.getGlobalBounds().width))))
	{
		// When the mouse is in sprite bounds and clicked...
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // Clicking the mouse starts the game
		{
			pAudioManager->PlaySoundFX("sounds/sfx_coin1.wav"); // Play Sound effect

			GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
			GameStateMenu* pGameStateMenu = new GameStateMenu;
			pGameStateManager->QueueGameState(pGameStateMenu);// Que GameStateMenu
		}
	}
}

void LevelEndScreen::GetPosition(int& x, int& y)
{
}

void LevelEndScreen::OnCollision(Collider2D* pCollider2D)
{
}
